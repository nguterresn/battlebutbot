#ifndef ESPNOW_H_
#define ESPNOW_H_

#include <WiFi.h>
#include "ESPNowW.h"

typedef struct esp_now_data {
    int roll;
    int pitch;
} esp_now_data;

void espnow_init(void);
void OnDataRecv(const uint8_t *mac_addr,const uint8_t *data, int data_len);


#endif /* ESPNOW_H_ */