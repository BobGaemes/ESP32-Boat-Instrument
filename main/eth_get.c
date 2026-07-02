#include "eth_get.h"
#include <string.h>
#include <stdbool.h>
#include "esp_log.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_eth.h"
#include "esp_http_client.h"
#include "ethernet_init.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

static const char *TAG = "eth_get";

#define ETH_GOT_IP_BIT BIT0
static EventGroupHandle_t s_eth_event_group;

static void got_ip_handler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    ip_event_got_ip_t *event = (ip_event_got_ip_t *)data;
    ESP_LOGI(TAG, "Got IP: " IPSTR, IP2STR(&event->ip_info.ip));
    xEventGroupSetBits(s_eth_event_group, ETH_GOT_IP_BIT);
}

esp_err_t eth_get(const char *url, char *buf, int buf_size)
{
    esp_http_client_config_t config = {
        .url = url,
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_http_client_set_method(client, HTTP_METHOD_GET);

    esp_err_t ret = ESP_FAIL;

    if (esp_http_client_open(client, 0) != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to open: %s", url);
        goto cleanup;
    }

    if (esp_http_client_fetch_headers(client) < 0)
    {
        ESP_LOGE(TAG, "Failed to fetch headers");
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
    }

cleanup:
    esp_http_client_close(client);
    esp_http_client_cleanup(client);
    return ret;
}

bool eth_init(uint32_t timeout_ms)
{
    s_eth_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_eth_handle_t *eth_handles;
    uint8_t eth_port_cnt;
    ESP_ERROR_CHECK(ethernet_init_all(&eth_handles, &eth_port_cnt)); // <-- changed

    esp_netif_config_t cfg = ESP_NETIF_DEFAULT_ETH();
    esp_netif_t *netif = esp_netif_new(&cfg);

    esp_eth_netif_glue_handle_t glue = esp_eth_new_netif_glue(eth_handles[0]);
    esp_netif_attach(netif, glue);

    esp_event_handler_register(IP_EVENT, IP_EVENT_ETH_GOT_IP, &got_ip_handler, NULL);
    esp_eth_start(eth_handles[0]);

    EventBits_t bits = xEventGroupWaitBits(s_eth_event_group, ETH_GOT_IP_BIT, false, true, pdMS_TO_TICKS(timeout_ms));
    return (bits & ETH_GOT_IP_BIT) != 0;
}
