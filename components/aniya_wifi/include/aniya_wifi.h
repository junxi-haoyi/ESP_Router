#pragma once


#include "string.h"

#include "esp_log.h"
#include "esp_err.h"

#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"


#include "lwip/opt.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "lwip/lwip_napt.h"

#include "dhcpserver/dhcpserver.h"


esp_err_t esp_gateway_wifi_napt_enable();
esp_err_t esp_gateway_wifi_set_dhcps(esp_netif_t *netif, uint32_t addr);
esp_err_t esp_gateway_wifi_sta_connected(uint32_t wait_ms);
esp_err_t esp_gateway_wifi_set(wifi_mode_t mode, const char *ssid, const char *password);
esp_netif_t *esp_gateway_wifi_init(wifi_mode_t mode);

static EventGroupHandle_t s_wifi_event_group = NULL;


