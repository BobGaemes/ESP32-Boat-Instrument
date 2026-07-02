#pragma once
#include "esp_err.h"
#include <stdbool.h>
#include <stdint.h>

void wifi_get_set_log_cb(void (*cb)(const char *msg, int level));
bool net_init(const char *ssid, const char *password, uint32_t timeout_ms);
esp_err_t wifi_get(const char *url, char *buf, int buf_size);