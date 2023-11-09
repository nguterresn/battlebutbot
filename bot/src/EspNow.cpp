#include <WiFi.h>
// #include <esp_wifi.h>
#include "EspNow.h"
#include "ESPNowW.h"

uint8_t mac_address[] = {0x08,0xB6,0x1F,0x29,0x9A,0x8C};

esp_now_data incomingData;

void espnow_init() {
    WiFi.mode(WIFI_MODE_STA);
    Serial.println(WiFi.macAddress());
    WiFi.disconnect();
    // Set custom mac address. Later on we can have channel selection for the bots.
    // Another alternative is to sync the transmitter with the bot through connecting
    // via wifi.
    // esp_wifi_set_mac(WIFI_IF_STA, mac_address);
    ESPNow.reg_recv_cb(OnDataRecv);
    ESPNow.init();
}

void OnDataRecv(const uint8_t *mac_addr,const uint8_t *data, int data_len) {
  memcpy(&incomingData, data, sizeof(incomingData));

  Serial.print(incomingData.pitch);
  Serial.print(" : ");
  Serial.println(incomingData.roll);
  Serial.print("\t");
}