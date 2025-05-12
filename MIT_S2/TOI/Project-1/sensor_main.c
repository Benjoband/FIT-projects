/**
 * @file main.c
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Implementation of TOI 1st project - part sensor - uses dallas thermometer to read temperature and send it to server using espnow.
 * @version 1.0
 * @date 2025-04-10
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_now.h"
#include "esp_netif.h"

#include "ds18x20.h"
#include "onewire.h"

#define TAG "SENDER"


#define SENSOR_GPIO GPIO_NUM_25 // GPIO pin for dallas thermometer

uint8_t receiver_mac[] = {0x7C, 0x9E, 0xBD, 0xF4, 0x5C, 0x41}; // MAC address of the receiver

static onewire_addr_t sensor_addr = ONEWIRE_NONE; // Global sensor address

/**
 * @brief Task that reads temperature and sends it via ESP-NOW every 5 seconds
 */
void sender_task(void *pvParameter) {
    while (1) {
        if (!onewire_reset(SENSOR_GPIO)) {
            ESP_LOGE(TAG, "Device not responding (reset failed)");
            vTaskDelay(pdMS_TO_TICKS(5000));
            continue;
        }

        ds18x20_measure(SENSOR_GPIO, sensor_addr, true);
        vTaskDelay(pdMS_TO_TICKS(750)); // wait for conversion

        float temp = 0.0;
        if (ds18x20_read_temperature(SENSOR_GPIO, sensor_addr, &temp) == ESP_OK) {
            esp_err_t result = esp_now_send(receiver_mac, (uint8_t *)&temp, sizeof(temp));
            if (result == ESP_OK) {
                ESP_LOGI(TAG, "Sent temperature: %.2f °C", temp);
            } else {
                ESP_LOGE(TAG, "Failed to send temperature");
            }
        } else {
            ESP_LOGW(TAG, "Failed to read temperature");
        }

        vTaskDelay(pdMS_TO_TICKS(5000)); // wait 5 seconds before next read
    }
}

/**
 * @brief Initialize Wi-Fi in station mode for ESP-NOW
 */
void initWifi() {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAG, "Wi-Fi initialized in station mode.");
}

/**
 * @brief Initialize ESP-NOW and add peer
 */
void initEspnow() {
    ESP_ERROR_CHECK(esp_now_init());
    ESP_ERROR_CHECK(esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE));
    esp_now_peer_info_t peer = {};
    memcpy(peer.peer_addr, receiver_mac, 6);
    peer.channel = 0;
    peer.encrypt = false;

    ESP_ERROR_CHECK(esp_now_add_peer(&peer));
    ESP_LOGI(TAG, "ESP-NOW initialized and peer added.");
}

/**
 * @brief Initialize one wire bus and search for dallas thermometer
 * 
 */
void initDallas()
{
    if (!onewire_reset(SENSOR_GPIO)) {
        ESP_LOGE(TAG, "No devices found on OneWire bus during setup.");
        return;
    }

    onewire_search_t search;
    onewire_search_start(&search);

    sensor_addr = onewire_search_next(&search, SENSOR_GPIO);
    if (sensor_addr == ONEWIRE_NONE) {
        ESP_LOGW(TAG, "No DS18B20 sensor found.");
        return;
    }

    ESP_LOGI(TAG, "Found sensor with ROM: 0x%llx", sensor_addr);
}
/**
 * @brief App entry point
 */
void app_main(void) {
    ESP_ERROR_CHECK(nvs_flash_init());

    // Initialize components
    initWifi();
    initEspnow();
    initDallas();

    // Start the temperature reading & sending task
    xTaskCreate(sender_task, "sender_task", 4096, NULL, 5, NULL);
}
