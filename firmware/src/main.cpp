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

  Serial.begin(9600);
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
