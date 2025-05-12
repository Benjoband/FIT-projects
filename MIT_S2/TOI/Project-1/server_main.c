/**
 * @file main.c
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Implementation of TOI 1st project - part web server - uses wifi AP mode to connect to ESP32 and receive temperature data via ESP-NOW.
 * @version 1.0
 * @date 2025-04-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_now.h"
#include "esp_spiffs.h"
#include "esp_http_server.h"

static const char *TAG = "SERVER";

#define MAX_TEMP_RECORDS 100 // maximum number of temperature records

/**
 * @brief Structure for holding temperature records in memory.
 * 
 */
typedef struct {
    time_t timestamp;
    float temperature;
} TempRecord;

static TempRecord records[MAX_TEMP_RECORDS]; // array to hold temperature records
static int record_count = 0; // number of records
static int record_index = 0; // for circular buffer of the temperature records

/**
 * @brief Structure to hold temperature statistics.
 */
typedef struct {
    float min;
    float max;
    float sum;
    float last;
    int count;
} TempStats;

/**
 * @brief Computes statistics from the temperature records.
 * 
 * @return TempStats 
 */
TempStats compute_stats() {
    TempStats stats = {
        .min = 1000.0f,
        .max = -1000.0f,
        .sum = 0.0f,
        .last = 0.0f,
        .count = 0
    };

    for (int i = 0; i < record_count; i++) {
        float temp = records[i].temperature;
        stats.sum += temp;
        stats.min = fminf(stats.min, temp);
        stats.max = fmaxf(stats.max, temp);
        stats.last = temp;
        stats.count++;
    }

    return stats;
}

/**
 * @brief Main communication function for receiving data from the ESP32.
 * 
 * @param mac_addr mac address of the sender
 * @param data data received
 * @param len length of the data
 */
static void on_data_recv(const uint8_t *mac_addr, const uint8_t *data, int len) {
    ESP_LOGI(TAG, "Received data from: %02x:%02x:%02x:%02x:%02x:%02x", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    if (len == sizeof(float)) {
        float temp;
        memcpy(&temp, data, sizeof(temp));
        ESP_LOGI(TAG, "Received temperature: %.2f", temp);

        records[record_index].timestamp = time(NULL);
        records[record_index].temperature = temp;

        record_index = (record_index + 1) % MAX_TEMP_RECORDS;
        if (record_count < MAX_TEMP_RECORDS) {
            record_count++;
        }
    } else {
        ESP_LOGW(TAG, "Invalid data size");
    }
}

/**
 * @brief Initializes the Wi-Fi AP mode for connecting to the ESP32 webserver.
 * 
 */
void init_wifi_ap() {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    wifi_config_t ap_config = {
        .ap = {
            .ssid = "ESP32-Web",
            .ssid_len = strlen("ESP32-Web"),
            .password = "esp32password",
            .max_connection = 2,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        }
    };
    if (strlen("esp32password") == 0) {
        ap_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &ap_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "Wi-Fi AP started. SSID: ESP32-Web, IP: 192.168.4.1");
}

/**
 * @brief Initializes ESP-NOW for receiving data.
 * 
 */
void init_espnow() {
    ESP_ERROR_CHECK(esp_now_init());
    ESP_ERROR_CHECK(esp_now_register_recv_cb(on_data_recv));
    ESP_LOGI(TAG, "ESP-NOW initialized and ready.");
}

/**
 * @brief Creates HTML content to be displayed on the webserver.
 * 
 * @param req 
 * @return esp_err_t 
 */
esp_err_t root_get_handler(httpd_req_t *req) {
    TempStats stats = compute_stats();

    char html[1024];
    int len = snprintf(html, sizeof(html),
        "<html><body>"
        "<h1>Temperature Stats</h1>"
        "<p>Total Readings: %d</p>"
        "<ul>"
        "<li><strong>Average:</strong> %.2f C</li>"
        "<li><strong>Min:</strong> %.2f C</li>"
        "<li><strong>Max:</strong> %.2f C</li>"
        "<li><strong>Last:</strong> %.2f C</li>"
        "</ul>",
        stats.count,
        stats.count > 0 ? stats.sum / stats.count : 0.0,
        stats.min,
        stats.max,
        stats.last
    );
    snprintf(html + len, sizeof(html) - len, "</body></html>");

    httpd_resp_send(req, html, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

/**
 * @brief Webserver initialization function. Starts the webserver where data will be displayed.
 *        Also creates 
 * 
 * @return httpd_handle_t 
 */
httpd_handle_t start_webserver(void) {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_uri_t root_uri = {
            .uri = "/",
            .method = HTTP_GET,
            .handler = root_get_handler,
            .user_ctx = NULL
        };
        httpd_register_uri_handler(server, &root_uri);
        ESP_LOGI(TAG, "HTTP server started");
    }
    return server;
}

/**
 * @brief Application main function - calling initialization functions
 * 
 */
void app_main(void) {
    ESP_ERROR_CHECK(nvs_flash_init());

    init_wifi_ap();
    init_espnow();
    start_webserver();
    
    uint8_t mac[6];
    esp_wifi_get_mac(WIFI_IF_AP, mac);
    ESP_LOGI("MAC", "MAC Address: %02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}
