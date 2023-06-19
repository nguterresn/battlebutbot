#include <Arduino.h>
#include "WebServer.h"

#define SERIAL_ENABLED 1

#define FEEDBACK_LED   D7

Robot robot(&Serial);

void setup()
{
#ifdef SERIAL_ENABLED
	Serial.begin(9600);
	Serial.print(F("Just initialized..."));
	#ifdef ESP8266
	Serial.print(F("ESP8266 defined."));
	#endif
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
