#include <Arduino.h>
#include "WebServer.h"

void setup()
{
	Serial.begin(9600);
	SPIFFS.begin();
	network_init();
	web_server_init();
}

void loop()
{
}
