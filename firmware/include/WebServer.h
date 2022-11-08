#ifndef SERVER_H
#define SERVER_H

#include <Arduino.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>

#include "html.h"

#define SSID_OF_THE_NETWORK "BubbleButBot"
#define DNS_NETWORK_NAME    "bot"

// HTTP QUERY
#define HTTP_QUERY_DEVICE "device"

// EVENTS TYPES
#define EVENT_SEND_SCANNED_DEVICE "scanned_device"

void notFound(AsyncWebServerRequest *request);
void setWebServer(unsigned char &stateMachineStep, String &bluetoothDeviceName);
void sendEvent(const char* type, char* value);
void setWifi();

#endif
