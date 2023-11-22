#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>

#include "Robot.h"

#define SSID_OF_THE_NETWORK "BattleButBot"
#define DNS_NETWORK_NAME    "bot"

// HTTP QUERY
#define HTTP_QUERY_DEVICE   "update"
#define HTTP_MOTOR_X        "x"
#define HTTP_MOTOR_Y        "y"
#define HTTP_CONFIG         "config"
#define HTTP_SPEED          "speed"
#define HTTP_MOTOR_DRIFT    "drift"

// EVENTS TYPES
#define EVENT_CONFIGURATION "configuration"

bool network_init(void);
bool spiffs_init(void);
void web_server_init(void);
void notFound(AsyncWebServerRequest* request);
void sendEvent(const char* type, int value);
