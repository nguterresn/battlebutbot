
#ifndef ESPNOW_H
#define ESPNOW_H

#include <WiFi.h>
#include <esp_now.h>
#include "MachineRoom.h"

typedef struct esp_now_data {
    int roll;
    int pitch;
} esp_now_data;

void initEspNow();
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len);
#endif /* ESPNOW_H */
