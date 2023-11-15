#include <Arduino.h>
#include "Debug.h"
#include "WebServer.h"
#include "EspNow.h"
#include "Robot.h"

void _error(void)
{
	while (1) {
		;
	}
}

void setup()
{
	D_SerialBegin(9600);

	if (!spiffs_init() || !network_init()) {
		_error();
	}

	web_server_init();

	if (!robot_init()) {
		_error();
	}

	initEspNow();
}

void loop()
{
}
