#include <Arduino.h>
#include "WebServer.h"
#include "Robot.h"

void setup()
{
	Serial.begin(9600);

	robot_init();

	network_init();
	web_server_init();
}

void loop()
{
}
