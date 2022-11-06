#include "WebServer.h"
#include "StateMachine.h"

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
/// @param stateMachineStep passed as reference
void setWebServer(unsigned char &stateMachineStep) {

  server.addHandler(&events);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", homePage);
  });

  server.on("/scan", HTTP_GET, [&stateMachineStep](AsyncWebServerRequest *request){
    // Give main loop a call to scan all the bluetooth devices
    stateMachineStep = SCAN_BLUETOOTH;
    request->send(200);
  });

  // server.on("/video", HTTP_GET, [](AsyncWebServerRequest *request){
  //  Another page. yet to be created!
  //  request->send(200, "text/html", homePage);
  // });

  server.onNotFound(notFound);
  server.begin();
}

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void sendEvent(const char* type, int value) {
  // char *buffer = new char[50];
  // intToConstChar(value, buffer);
  // events.send(buffer, type, millis());
  // delete []buffer;
}
