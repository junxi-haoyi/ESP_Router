/*  WiFi softAP Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_mac.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include "aniya_wifi.h"


void app_main(void)
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    esp_netif_t *sta_wifi_netif = esp_gateway_wifi_init(WIFI_MODE_STA);
    esp_gateway_wifi_set(WIFI_MODE_STA, "510", "510510510");
    esp_gateway_wifi_sta_connected(portMAX_DELAY);

    esp_netif_t *ap_wifi_netif = esp_netif_create_default_wifi_ap();
    esp_netif_dns_info_t dns;
    ESP_ERROR_CHECK(esp_netif_get_dns_info(sta_wifi_netif, ESP_NETIF_DNS_MAIN, &dns));
    ESP_LOGI("gateway_wifi", "Main DNS: " IPSTR, IP2STR(&dns.ip.u_addr.ip4));
    ESP_ERROR_CHECK(esp_gateway_wifi_set_dhcps(ap_wifi_netif, dns.ip.u_addr.ip4.addr));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
    esp_gateway_wifi_set(WIFI_MODE_AP, "haojie_esp32", "123456789");
    esp_gateway_wifi_napt_enable();
}
