#include "WebServer.h"

AsyncWebServer server(80);
AsyncEventSource events("/events");

/// @brief Initialize ESP as a Access Point. Give it a SSID(name) and a custom DNS domain.
void setWifi() {
  // Disable power saving on WiFi to improve responsiveness
  // (https://github.com/espressif/arduino-esp32/issues/1484)
  WiFi.setSleep(false);
  WiFi.softAP(SSID_OF_THE_NETWORK);
  MDNS.begin(DNS_NETWORK_NAME);
  MDNS.addService("http", DNS_NETWORK_NAME, 80);
}

/// @brief Function to create all the endpoints and respective handlers for the WebServer.
void setWebServer(Motor &motor) {

  server.addHandler(&events);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", homePage);
  });

  server.on("/update", HTTP_GET, [&motor](AsyncWebServerRequest *request) {
    if (request->hasParam(HTTP_MOTOR_X) && request->hasParam(HTTP_MOTOR_Y)) {
      motor.update(
        request->getParam(HTTP_MOTOR_X)->value().toInt(),
        request->getParam(HTTP_MOTOR_Y)->value().toInt()
      );
      request->send(200, "text/plain", "OK");
    }
    request->send(404, "text/plain");
  });

  server.onNotFound(notFound);
  server.begin();
}

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

/// @brief Send an event to web client
/// @param type type of the event
/// @param value string to be sent
void sendEvent(const char* type, char* value) {
  events.send(value, type, millis());
}
