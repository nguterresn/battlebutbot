#ifndef SERVER_H
#define SERVER_H

#include <Arduino.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>

#include "html.h"
#include "Motor.h"

#define SSID_OF_THE_NETWORK "BubbleButBot"
#define DNS_NETWORK_NAME    "bot"

// HTTP QUERY
#define HTTP_QUERY_DEVICE "update"
#define HTTP_MOTOR_X "x"
#define HTTP_MOTOR_Y "y"

// EVENTS TYPES
#define EVENT_SEND_SCANNED_DEVICE "scanned_device"

void notFound(AsyncWebServerRequest *request);
void setWebServer(Motor &motor);
void sendEvent(const char* type, char* value);
void setWifi();

#endif
