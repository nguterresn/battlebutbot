#include "WebServer.h"

AsyncWebServer server(80);

/// @brief Initialize ESP as a Access Point. Give it a SSID(name) and a custom DNS domain.
void setWifi() {
  // Disable power saving on WiFi to improve responsiveness
  // (https://github.com/espressif/arduino-esp32/issues/1484)
  WiFi.setSleep(false);
  // Limit the amount of connections to the same web server.  One user per device.
  WiFi.softAP(SSID_OF_THE_NETWORK, NULL, 1, 0, 1);
  MDNS.begin(DNS_NETWORK_NAME);
  MDNS.addService("http", DNS_NETWORK_NAME, 80);
}

/// @brief Function to create all the endpoints and respective handlers for the WebServer.
void setWebServer(MachineRoom &machineRoom) {

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", homePage);
  });

  server.on("/update", HTTP_GET, [&machineRoom](AsyncWebServerRequest *request) {
    if (request->hasParam(HTTP_MOTOR_X) && request->hasParam(HTTP_MOTOR_Y)) {
      machineRoom.update(
        request->getParam(HTTP_MOTOR_X)->value().toInt(),
        request->getParam(HTTP_MOTOR_Y)->value().toInt()
      );
      request->send(200, "text/plain", "OK");
      return;
    }
    request->send(404, "text/plain");
  });

  server.on("/action", HTTP_GET, [](AsyncWebServerRequest *request){
    // Do something later on, need to add the hardware first.
    request->send(200, "text/plain", "OK");
  });

  server.onNotFound(notFound);
  server.begin();
}

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
