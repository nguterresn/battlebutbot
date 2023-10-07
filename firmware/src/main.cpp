#include <Arduino.h>
#include "WebServer.h"

Robot robot;

void setup() {
	SPIFFS.begin();
	setWifi();
	setWebServer(robot);
}

void loop() {
}
