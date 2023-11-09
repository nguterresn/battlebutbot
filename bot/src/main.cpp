#include <Arduino.h>
#include <WiFi.h>
#include "ESPNowW.h"
#include "EspNow.h"
// #include "Robot.h"

#define DEBUG


void setup()
{
	#ifdef DEBUG
	// delay(500);
	Serial.begin(115200);
	Serial.println("Starting..");
	#endif
	// espnow_init();
	// robot_init();
}

void loop()
{
}
