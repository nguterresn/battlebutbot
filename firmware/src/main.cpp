#include <Arduino.h>
#define SERIAL_ENABLED 1

#define FEEDBACK_LED   D7
#define USE_ESP_NOW 1

#ifdef USE_ESP_NOW
#include "EspNowReceiver.h"
#else
#include "WebServer.h"
#endif

Robot robot(&Serial);

void setup()
{
#ifdef SERIAL_ENABLED
	Serial.begin(115200);
	Serial.print(F("Just initialized..."));
	#ifdef ESP8266
	Serial.print(F("ESP8266 defined."));
	#endif
#endif

#ifdef USE_ESP_NOW
	initEspNow();
#else
	SPIFFS.begin();
	setWifi();
	setWebServer(robot);
	#endif
}

void loop()
{
#ifdef USE_ESP_NOW
#else
#ifdef ESP8266
	MDNS.update();
#endif
#endif
}
