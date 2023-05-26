#ifndef SERVER_H
#define SERVER_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPmDNS.h>
#elif ESP8266
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESP8266mDNS.h>
#endif

#include "Robot.h"

#define SSID_OF_THE_NETWORK "BattleButBot"
#define DNS_NETWORK_NAME    "bot"

// HTTP QUERY
#define HTTP_QUERY_DEVICE   "update"
#define HTTP_MOTOR_X        "x"
#define HTTP_MOTOR_Y        "y"
#define HTTP_CONFIG         "config"
#define HTTP_SPEED          "speed"
#define HTTP_FRICTION       "friction"

// EVENTS TYPES
#define EVENT_CONFIGURATION "configuration"

void notFound(AsyncWebServerRequest* request);
void setWebServer(Robot& robot);
void sendEvent(const char* type, int value);
void setWifi();

#endif
