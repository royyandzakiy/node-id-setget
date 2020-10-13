#include "nodeid.h"

esp_err_t err;
nvs_handle_t my_handle;

void init_nvs() {
    err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );
}

uint8_t get_nodeid() {
    uint8_t nodeid = 230; // value will default to 0, if not set yet in NVS
    err = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK) {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    } else {
        // printf("Reading Node ID from NVS ... ");
        err = nvs_get_u8(my_handle, "nodeid", &nodeid);
        switch (err) {
            case ESP_OK:
                // printf("Node ID = %d\n", nodeid);
                break;
            case ESP_ERR_NVS_NOT_FOUND:
                printf("The value is not initialized yet!\n");
                break;
            default :
                printf("Error (%s) reading!\n", esp_err_to_name(err));
        }
    }
    return nodeid;
}

void set_nodeid(uint8_t nodeid) {
    err = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK) {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    } else {
        // Write
        err = nvs_set_u8(my_handle, "nodeid", nodeid);
        printf((err != ESP_OK) ? "Failed!\n" : "");
        Serial.print("Node ID set: ");
        Serial.println(nodeid);

        // Commit written value.
        // After setting any values, nvs_commit() must be called to ensure changes are written
        // to flash storage. Implementations may write to storage at other times,
        // but this is not guaranteed.
        err = nvs_commit(my_handle);
        printf((err != ESP_OK) ? "Failed!\n" : "");

        // Close
        nvs_close(my_handle);
    }
}

void restart_module() {
    // Restart module
    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}