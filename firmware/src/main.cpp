#include <Arduino.h>
#include "WebServer.h"

Robot robot;

void setup()
{
	Serial.begin(9600);
	SPIFFS.begin();
	setWifi();
	setWebServer(robot);
}

void loop()
{
}
