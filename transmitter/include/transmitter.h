
#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <WiFi.h>
#include "ESPNowW.h"

#define TRANSMITTER_INTERVAL 25

typedef struct esp_now_data {
	int roll;
	int pitch;
} esp_now_data;

void transmitter_begin();
void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status);
void transmitter_loop(void* v);

#endif /* TRANSMITTER_H */