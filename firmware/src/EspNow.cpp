#include "EspNow.h"
#include "Debug.h"

esp_now_data recEspNowData;

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len);

void initEspNow() {
    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);
    D_print("Wifi Mac: ");
    D_println(WiFi.macAddress());
    WiFi.disconnect();

  if (esp_now_init() != 0) {
    D_println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
    esp_now_data* new_data = (esp_now_data*) data;
    if (new_data->pitch == recEspNowData.pitch && new_data->roll == recEspNowData.roll) {
        return;
    }
    memcpy(&recEspNowData, data, sizeof(recEspNowData));
    D_print("pr\t");
    D_print(recEspNowData.pitch);
    D_print("\t");
    D_println(recEspNowData.roll);
    // Handle data received.
    machine_room_update(recEspNowData.pitch, recEspNowData.pitch);
}