#ifndef ESPNOWRECEIVER_H
#define ESPNOWRECEIVER_H

#ifdef ESP32
#elif ESP8266
#include <ESP8266WiFi.h>
#endif

#include <espnow.h>
#include "Robot.h"

extern Robot robot;

typedef struct esp_now_data {
    int roll;
    int pitch;
} esp_now_data;

void initEspNow();
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len);
#endif
