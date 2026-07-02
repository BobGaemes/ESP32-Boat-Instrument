#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_check.h"
#include "esp_memory_utils.h"
#include "lvgl.h"
#include "bsp/esp-bsp.h"
#include "bsp/display.h"
#include "bsp_board_extra.h"
#include "string.h"
#include "stdlib.h"
#include "esp_task_wdt.h"   

#include "ui.h"
#include "vars.h"
// #include "eth_get.h"
#include "wifi_get.h"

#define TAG "main"

#define SIGNALK_BASE "http://10.37.88.174:3000/signalk/v1/api/vessels/self"

#define WIFI_SSID ""
#define WIFI_PASS ""

static bool first_data = true;

#define UI_LOG(msg)           \
    do                        \
    {                         \
        bsp_display_lock(-1); \
        ui_log(msg);          \
        bsp_display_unlock(); \
    } while (0)

static void net_log_cb(const char *msg, int level)
{
    bsp_display_lock(-1);
    ui_log_level(msg, (ui_log_level_t)level);
    bsp_display_unlock();
}

char buf[2048];
static void wifi_task(void *pvParameters)
{
    UI_LOG("Starting WiFi...");
    char msg0[128];
    snprintf(msg0, sizeof(msg0), "SSID: %s", WIFI_SSID);
    UI_LOG(msg0);
    net_init(WIFI_SSID, WIFI_PASS, 15000);

    char msg1[128];
    snprintf(msg1, sizeof(msg1), "Fetching SignalK... (%s)", SIGNALK_BASE);
    UI_LOG(msg1);
    esp_task_wdt_add(NULL);

    while (1)
    {
        esp_task_wdt_reset();

        if (wifi_get(SIGNALK_BASE "/environment/wind/angleApparent/value", buf, sizeof(buf)) == ESP_OK)
        {
            if (first_data)
            {
                first_data = false;
                bsp_display_lock(-1);
                ui_hide_log();
                bsp_display_unlock();
            }

            ESP_LOGI(TAG, "AWA: %s", buf);
            set_var_apparent_wind_angle_value(atof(buf));
        }
        if (wifi_get(SIGNALK_BASE "/environment/wind/directionTrue/value", buf, sizeof(buf)) == ESP_OK)
        {
            ESP_LOGI(TAG, "TWA: %s", buf);
            set_var_true_wind_angle_value(atof(buf));
        }
        if (wifi_get(SIGNALK_BASE "/environment/wind/speedTrue/value", buf, sizeof(buf)) == ESP_OK)
        {
            ESP_LOGI(TAG, "TWS: %s", buf);
            set_var_true_wind_speed_value(atof(buf));
        }
        if (wifi_get(SIGNALK_BASE "/environment/wind/speedApparent/value", buf, sizeof(buf)) == ESP_OK)
        {
            ESP_LOGI(TAG, "AWS: %s", buf);
            set_var_apparent_wind_speed_value(atof(buf));
        }
        if (wifi_get(SIGNALK_BASE "/navigation/courseOverGroundTrue/value", buf, sizeof(buf)) == ESP_OK)
        {
            ESP_LOGI(TAG, "COG: %s", buf);
            set_var_course_over_ground_value(atof(buf));
        }
        if (wifi_get(SIGNALK_BASE "/navigation/speedThroughWater/value", buf, sizeof(buf)) == ESP_OK)
        {
            ESP_LOGI(TAG, "STW: %s", buf);
            set_var_speed_through_water_value(atof(buf));
        }
        if (wifi_get(SIGNALK_BASE "/navigation/speedOverGround/value", buf, sizeof(buf)) == ESP_OK)
        {
            ESP_LOGI(TAG, "SOG: %s", buf);
            set_var_speed_over_ground_value(atof(buf));
        }
        if (wifi_get(SIGNALK_BASE "/performance/velocityMadeGood/value", buf, sizeof(buf)) == ESP_OK)
        {
            ESP_LOGI(TAG, "VMG: %s", buf);
            set_var_velocity_made_good_value(atof(buf));
        }
        if (wifi_get(SIGNALK_BASE "/performance/polarSpeedRatio/value", buf, sizeof(buf)) == ESP_OK)
        {
            ESP_LOGI(TAG, "PPR: %s", buf);
            set_var_polar_performance_ratio_value(atof(buf));
        }
        if (wifi_get(SIGNALK_BASE "/navigation/attitude/value/roll", buf, sizeof(buf)) == ESP_OK)
        {
            ESP_LOGI(TAG, "ROLL: %s", buf);
            set_var_heel_scale_value(atof(buf));
        }
        if (wifi_get(SIGNALK_BASE "/navigation/state/value", buf, sizeof(buf)) == ESP_OK)
        {
            ESP_LOGI(TAG, "STATE: %s", strupr(buf));
            set_var_boat_status_value(strupr(buf));
        }

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    ESP_LOGE("main", "STACK OVERFLOW in task: %s", pcTaskName);
    abort();
}

void app_main(void)
{

    /*
    If you need to use the three-cache anti-tear configuration, you need to fix idf 5.5. Refer to: https://github.com/espressif/esp-iot-solution/blob/da973d162cc88736a4e05e6582393e666f221c2a/components/display/tools/esp_lvgl_adapter/README.md?plain=1#L671-L709
    */
    bsp_display_cfg_t cfg = {
        .lv_adapter_cfg = ESP_LV_ADAPTER_DEFAULT_CONFIG(),
        .rotation = ESP_LV_ADAPTER_ROTATE_0,
        .tear_avoid_mode = ESP_LV_ADAPTER_TEAR_AVOID_MODE_TRIPLE_PARTIAL,
        .touch_flags = {
            .swap_xy = 0,
            .mirror_x = 1,
            .mirror_y = 1
        }};
    bsp_display_start_with_config(&cfg);
    bsp_display_backlight_on();

    bsp_display_lock(-1);

    ui_init();

    bsp_display_unlock();

    wifi_get_set_log_cb(net_log_cb);
    xTaskCreatePinnedToCore(wifi_task, "wifi", 8192, NULL, 5, NULL, 1);

    while (1)
    {
        bsp_display_lock(-1);
        ui_tick();
        bsp_display_unlock();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
