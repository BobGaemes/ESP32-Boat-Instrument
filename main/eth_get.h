#pragma once

#include "esp_err.h"
#include "stdbool.h"

bool eth_init(uint32_t timeout_ms); // returns true if got IP
esp_err_t eth_get(const char *url, char *buf, int buf_size);