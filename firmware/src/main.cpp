#include <Arduino.h>
#include "WebServer.h"

#define SERIAL_ENABLED 1

Robot robot(&Serial);

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
