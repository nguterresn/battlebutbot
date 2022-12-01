#include <Arduino.h>
#include "WebServer.h"

#define LED_FLASH 4
#define LED_ON_BOARD 33

#define SERIAL_ENABLED 1

Motor motor;

void setup() {
  pinMode(33, OUTPUT);

  #ifdef SERIAL_ENABLED
  Serial.begin(9600);
  Serial.print("Just initialized...");
  motor.installLogger(&Serial);
  #endif

  setWifi();
  setWebServer(motor);
}

void loop() {}
