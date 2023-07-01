#include <Arduino.h>
#include "WebServer.h"

Robot robot;

// Main function runs as C and not C++
extern "C" void app_main();
void app_main(void)
{
	initArduino();

	SPIFFS.begin();
	setWifi();
	setWebServer(robot);
}
