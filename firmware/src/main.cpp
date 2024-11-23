#include "MachineRoom.h"
#include "Robot.h"
#include "WebServer.h"
#include <Arduino.h>
#include <math.h>
#ifdef PHYSYCAL_CONTROLLER
#include <esp_wifi.h>
#include <esp_now.h>

static void on_data_recv(const uint8_t *mac, const uint8_t *incomingData,
                         int len);
#endif

void _error(void) {
  while (1) {
    ;
  }
}

void setup() {
  Serial.begin(9600);
  Serial.printf("Connected!\n");

  if (!spiffs_init() || !network_init()) {
    _error();
  }

  web_server_init();
#ifdef PHYSYCAL_CONTROLLER
  if (esp_now_init() != ESP_OK) {
    _error();
  }
  esp_now_register_recv_cb(esp_now_recv_cb_t(on_data_recv));
#endif

  if (!robot_init()) {
    _error();
  }
}

void loop() {}

#ifdef PHYSYCAL_CONTROLLER
static void on_data_recv(const uint8_t *mac, const uint8_t *incomingData,
                         int len) {
  struct packet {
    int8_t speed;
    int8_t y;
    int8_t x;
  } __attribute__((packed));
  struct packet *coor = (struct packet *)incomingData;

  // Serial.printf(" sin_mapped_y: %d | mapped_speed: %d | mapped_x: %d |
  // mapped_y: %d | radian: %f len: %d \n", sin_mapped_y, coor->speed, coor->x,
  // coor->y, radian, len);

  machine_room_update(coor->speed, coor->y, coor->x);
}
#endif
