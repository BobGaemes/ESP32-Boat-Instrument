#include "wifi_get.h"
#include <string.h>
#include "esp_log.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_http_client.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "nvs_flash.h"

static const char *TAG = "wifi_get";
#define WIFI_GOT_IP_BIT BIT0
#define WIFI_FAIL_BIT BIT1
static EventGroupHandle_t s_wifi_event_group;

#define WIFI_MAX_RETRY 5
static int s_retry_num = 0;

static void (*s_log_cb)(const char *msg, int level) = NULL;

void wifi_get_set_log_cb(void (*cb)(const char *msg, int level))
{
    s_log_cb = cb;
}

#define NET_LOG_INFO(msg)  do { if (s_log_cb) s_log_cb(msg, 0); } while(0)
#define NET_LOG_WARN(msg)  do { if (s_log_cb) s_log_cb(msg, 1); } while(0)
#define NET_LOG_ERR(msg)   do { if (s_log_cb) s_log_cb(msg, 2); } while(0)

static void wifi_event_handler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    if (base == WIFI_EVENT && id == WIFI_EVENT_STA_START)
    {
        esp_wifi_connect(); 
    }
    else if (base == WIFI_EVENT && id == WIFI_EVENT_STA_DISCONNECTED)
    {
        wifi_event_sta_disconnected_t *event = (wifi_event_sta_disconnected_t *)data;
        char msg[64];
        snprintf(msg, sizeof(msg), "WiFi disconnected, reason: %d", event->reason);
        NET_LOG_ERR(msg);
        if (s_retry_num < WIFI_MAX_RETRY)
        {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGW(TAG, "Retrying WiFi (%d/%d)...", s_retry_num, WIFI_MAX_RETRY);
            char msg[64];
            snprintf(msg, sizeof(msg), "Retrying WiFi (%d/%d)...", s_retry_num, WIFI_MAX_RETRY);
            NET_LOG_WARN(msg);
        }
        else
        {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
    }
    else if (base == IP_EVENT && id == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)data;
        ESP_LOGI(TAG, "Got IP: " IPSTR, IP2STR(&event->ip_info.ip));
        char msg[64];
        snprintf(msg, sizeof(msg), "Got IP: " IPSTR, IP2STR(&event->ip_info.ip));
        NET_LOG_INFO(msg);
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_GOT_IP_BIT);
    }
}

bool net_init(const char *ssid, const char *password, uint32_t timeout_ms)
{
    esp_err_t nvs_ret = nvs_flash_init();
    if (nvs_ret == ESP_ERR_NVS_NO_FREE_PAGES || nvs_ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        nvs_ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(nvs_ret);

    s_wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t wcfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&wcfg));

    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL);
    
    wifi_config_t wifi_cfg = {
        .sta = {
            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
        },
    };
    strlcpy((char *)wifi_cfg.sta.ssid, ssid, sizeof(wifi_cfg.sta.ssid));
    strlcpy((char *)wifi_cfg.sta.password, password, sizeof(wifi_cfg.sta.password));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());

    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                           WIFI_GOT_IP_BIT | WIFI_FAIL_BIT, false, false, pdMS_TO_TICKS(timeout_ms));
    return (bits & WIFI_GOT_IP_BIT) != 0;
}

esp_err_t wifi_get(const char *url, char *buf, int buf_size)
{
    esp_http_client_config_t config = {
        .url = url,
        .timeout_ms = 2000
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_http_client_set_method(client, HTTP_METHOD_GET);
    esp_err_t ret = ESP_FAIL;

    if (esp_http_client_open(client, 0) != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to open: %s", url);
        char msg[128];
        snprintf(msg, sizeof(msg), "Failed to open: %s", url); // just show path end
        NET_LOG_ERR(msg);
        goto cleanup;
    }
    if (esp_http_client_fetch_headers(client) < 0)
    {
        ESP_LOGE(TAG, "Failed to fetch headers");
        NET_LOG_ERR("Failed to fetch headers");
        goto cleanup;
    }
    int data_read = esp_http_client_read_response(client, buf, buf_size - 1);
    if (data_read >= 0)
    {
        buf[data_read] = '\0';
        ret = ESP_OK;
    }
    else
    {
        ESP_LOGE(TAG, "Failed to read response");
        NET_LOG_ERR("Failed to read response");
    }
cleanup:
    esp_http_client_close(client);
    esp_http_client_cleanup(client);
    return ret;
}