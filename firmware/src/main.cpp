#include <Arduino.h>
#include "WebServer.h"
#include "Robot.h"

void _error(void)
{
	while (1) {
		;
	}
}

void setup()
{
	if (!spiffs_init() || !network_init()) {
		_error();
	}

	web_server_init();

	if (!robot_init()) {
		_error();
	}
}

void loop()
{
}
