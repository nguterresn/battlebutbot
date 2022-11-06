#ifndef SERVER_H
#define SERVER_H

#include <Arduino.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>

#include "html.h"

#define SSID_OF_THE_NETWORK "BubbleButBot"
#define DNS_NETWORK_NAME    "bot"

void notFound(AsyncWebServerRequest *request);
void setWebServer(unsigned char &stateMachineStep);
void sendEvent(const char* type, int value);
void setWifi();

#endif
