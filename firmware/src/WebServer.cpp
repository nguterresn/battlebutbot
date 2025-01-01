#include "WebServer.h"
#include "MachineRoom.h"
#include "Robot.h"
#include <SPIFFS.h>
#ifdef PHYSYCAL_CONTROLLER
#include <esp_wifi.h>
static uint8_t _mac_address[] = { 0x1A, 0xFF, 0x00, 0xFF, 0x00, 0xFF };
#endif

AsyncWebServer server(80);
String mac_address;

/// @brief Initialize ESP as a Access Point. Give it a SSID(name) and a custom
/// DNS domain.
bool network_init(void)
{
#ifdef PHYSYCAL_CONTROLLER
  WiFi.mode(WIFI_STA);
  WiFi.begin();
  esp_err_t err = esp_wifi_set_mac(WIFI_IF_STA, _mac_address);
  if (err != ERR_OK) {
    return false;
  }
#endif
  // Disable power saving on WiFi to improve responsiveness
  // (https://github.com/espressif/arduino-esp32/issues/1484)
  if (!WiFi.setSleep(false) ||
      // Limit the amount of connections to the same web
      // server.  One user per device.
      !WiFi.softAP(SSID_OF_THE_NETWORK, NULL, 1, 0, 1) ||
      !MDNS.begin(DNS_NETWORK_NAME) ||
      !MDNS.addService("http", DNS_NETWORK_NAME, 80)) {
    return false;
  }
  mac_address = WiFi.macAddress();
  return true;
}

String processor(const String& var)
{
  if (var == "DEVICE_ID") {
    return mac_address;
  }
  return String();
}

bool spiffs_init(void)
{
  Serial.printf("Setting SPIFFS!....\n");
  return SPIFFS.begin();
}

/// @brief Function to create all the endpoints and respective handlers for the
/// WebServer.
void web_server_init()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (request->hasParam(HTTP_SPEED)) {
      robot_save_configuration(request->getParam(HTTP_SPEED)->value().toInt());
    }
    else {
      robot_connect();
    }
    // https://arduino-esp8266.readthedocs.io/en/latest/filesystem.html
    request->send(SPIFFS, "/main.html", "text/html", false, processor);
  });

  server.on("/config", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(SPIFFS, "/config.html", "text/html");
  });

  server.on("/load-configuration", HTTP_GET,
            [](AsyncWebServerRequest* request) {
    char buffer[10] = { 0 };
    if (robot_serialize_for_request(buffer)) {
      request->send(200, "text/plain", buffer);
    }
  });

  server.on("/update", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (request->hasParam(HTTP_MOTOR_SPEED) &&
        request->hasParam(HTTP_MOTOR_Y) &&
        request->hasParam(HTTP_MOTOR_X)) {
      machine_room_update(request->getParam(HTTP_MOTOR_SPEED)->value().toInt(),
                          request->getParam(HTTP_MOTOR_Y)->value().toInt(),
                          request->getParam(HTTP_MOTOR_X)->value().toInt());
      request->send(200, "text/plain", "OK");
      return;
    }
    request->send(404, "text/plain");
  });

  // --- Expose the files from SPIFFS --- //

  server.on("/index.css", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(SPIFFS, "/index.css", "text/css");
  });
  server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(SPIFFS, "/main.js", "text/javascript");
  });
  server.on("/utils.js", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(SPIFFS, "/utils.js", "text/javascript");
  });
  server.on("/joystick.js", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(SPIFFS, "/joystick.js", "text/javascript");
  });

  server.onNotFound(notFound);
  server.begin();
}

void notFound(AsyncWebServerRequest* request)
{
  request->send(404, "text/plain", "Not found " + request->url());
}
