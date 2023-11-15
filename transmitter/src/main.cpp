#include <Arduino.h>
#include <WiFi.h>
#include "ESPNowW.h"

#define TRANSMITTER
#define POT_X 35
#define POT_Y 34

#define TRANSMITTER_INTERVAL 25

// REPLACE WITH THE MAC Address of your receiver 
uint8_t recmac[] = {0x08,0xB6,0x1F,0x29,0x9A,0x8C};
uint8_t transmac[] = {0x3C,0x71,0xBF,0x9D,0x9F,0x88};

typedef struct esp_now_data {
    int roll;
    int pitch;
} esp_now_data;

unsigned long previousMillis = 0;
esp_now_data data;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  Serial.println("starting..");
  WiFi.mode(WIFI_MODE_STA);

  Serial.println(WiFi.macAddress());
  // ESPNow.set_mac(transmac);
  WiFi.disconnect();
  ESPNow.init();
  ESPNow.add_peer(recmac);
  // ESPNow.reg_send_cb(OnDataSent);

  pinMode(POT_X, INPUT);
  pinMode(POT_Y, INPUT);
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= TRANSMITTER_INTERVAL) {
    previousMillis = currentMillis;

    int p = map(analogRead(POT_Y), 0, 4095, -100, 100);
    int r = map(analogRead(POT_X), 0, 4095, -100, 100);
    p = constrain(p, -100, 100);
    r = constrain(r, -100, 100);
    if (abs(p) < 30) p = 0;
    if (abs(r) < 30) r = 0;

    if (p == data.pitch && r == data.roll) {
      return;
    }
    data.pitch = p;
    data.roll = r;

    Serial.println(p);
    Serial.println(r);

    ESPNow.send_message(recmac, (uint8_t *) &data, sizeof(data));
  }
}

