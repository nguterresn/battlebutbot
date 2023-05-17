#include <Arduino.h>
#include "WebServer.h"

#define SERIAL_ENABLED 1

#define LEFT1          D1
#define LEFT2          D2
#define RIGHT1         D5
#define RIGHT2         D4

#define FEEDBACK_LED   D7

Robot robot(LEFT1, LEFT2, RIGHT1, RIGHT2, FEEDBACK_LED, &Serial);

void setup()
{
#ifdef SERIAL_ENABLED
	Serial.begin(9600);
	Serial.print(F("Just initialized..."));
#endif

	SPIFFS.begin();
	setWifi();
	setWebServer(robot);
}

void loop()
{
#ifdef ESP8266
	MDNS.update();
#endif
}
