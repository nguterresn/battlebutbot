#include <Arduino.h>
#include "WebServer.h"
#include "Robot.h"

void setup()
{
	robot_init();

	network_init();
	web_server_init();
}

void loop()
{
}
