#include <Arduino.h>
#include "WebServer.h"

#define SERIAL_ENABLED 1

MachineRoom machineRoom(D1, D2, D5, D4);

void setup() {
  #ifdef SERIAL_ENABLED
  Serial.begin(9600);
  Serial.print(F("Just initialized..."));
  machineRoom.installLogger(&Serial);
  #endif

  setWifi();
  setWebServer(machineRoom);
}

void loop() {
  #ifdef ESP8266
  MDNS.update();
  #endif
  // There are some limitations with the heap memory.
  // The usage of the webserver for more than ~30 seconds will cause the
  // esp to crash (out of heap memory).
  // Serial.println(ESP.getFreeHeap());
}
