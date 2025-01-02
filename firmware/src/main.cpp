#include "MachineRoom.h"
#include "Robot.h"
#include "WebServer.h"
#include <Arduino.h>
#include <math.h>
#ifdef PHYSYCAL_CONTROLLER
#include <esp_wifi.h>
#include <esp_now.h>
static uint8_t _mac_address[] = { 0x1A, 0xFF, 0x00, 0xFF, 0x00, 0xFF };

static void on_data_recv(const uint8_t *mac, const uint8_t *incomingData,
                         int len);
#endif

void _error(void) {
  while (1) {
    ;
  }
}

void setup() {
  Serial.begin(115200);
  Serial.printf("Connected!\n");

  if (!spiffs_init() || !network_init()) {
    _error();
  }

#ifdef PHYSYCAL_CONTROLLER
  // The station MAC Address must differ from the softAP one.
  if (esp_wifi_set_mac(WIFI_IF_STA, _mac_address) != ESP_OK || esp_now_init() != ESP_OK) {
    _error();
  }
  esp_now_register_recv_cb(esp_now_recv_cb_t(on_data_recv));
#endif
  web_server_init();

  if (!robot_init()) {
    _error();
  }

  Serial.printf("Robot initialized!\n");
}

void loop() { yield(); }

#ifdef PHYSYCAL_CONTROLLER
static void on_data_recv(const uint8_t *mac, const uint8_t *incomingData,
                         int len) {
  struct packet {
    int8_t speed;
    int8_t y;
    int8_t x;
  } __attribute__((packed));
  struct packet *coor = (struct packet *)incomingData;

  machine_room_update(coor->speed, coor->y, coor->x);
}
#endif
