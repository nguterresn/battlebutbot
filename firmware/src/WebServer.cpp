#include "WebServer.h"
#include "Robot.h"
#include "MachineRoom.h"
#include "Debug.h"
#include <SPIFFS.h>

AsyncWebServer server(80);

/// @brief Initialize ESP as a Access Point. Give it a SSID(name) and a custom DNS domain.
bool network_init(void)
{
	// Disable power saving on WiFi to improve responsiveness
	// (https://github.com/espressif/arduino-esp32/issues/1484)

	if (!WiFi.setSleep(false)) {
		D_println("WiFi.setSleep failed");
		return false;
	} else if (!WiFi.softAP(SSID_OF_THE_NETWORK, NULL, 1, 0, 1)) {
		D_println("WiFi.softAP failed");
		return false;
	} else if (!MDNS.begin(DNS_NETWORK_NAME)) {
		D_println("MDNS.begin failed");
		return false;
	} else if (!MDNS.addService("http", DNS_NETWORK_NAME, 80)) {
		D_println("MDNS.addService failed");
		return false;
	}
	return true;
}

bool spiffs_init(void)
{
	if (!SPIFFS.begin()) {
		D_println("SPIFFS.begin failed");
		return false;
	}
	return true;
}

/// @brief Function to create all the endpoints and respective handlers for the WebServer.
void web_server_init()
{
	server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
		if (request->hasParam(HTTP_CONFIG) && request->hasParam(HTTP_SPEED)) {
			robot_save_configuration(request->getParam(HTTP_CONFIG)->value().toInt(),
			                         request->getParam(HTTP_SPEED)->value().toInt(),
			                         request->getParam(HTTP_DRIFT)->value().toInt());
		}
		else {
			robot_connect();
		}
		// https://arduino-esp8266.readthedocs.io/en/latest/filesystem.html
		request->send(SPIFFS, "/home.html", "text/html");
	});

	server.on("/index.css", HTTP_GET, [](AsyncWebServerRequest* request){
		request->send(SPIFFS, "/index.css", "text/css");
	});

	server.on("/config", HTTP_GET, [](AsyncWebServerRequest* request){
		request->send(SPIFFS, "/config.html", "text/html");
	});

	server.on("/load-configuration", HTTP_GET, [](AsyncWebServerRequest* request){
		char buffer[10] = { 0 };
		if (robot_serialize_for_request(buffer)) {
			request->send(200, "text/plain", buffer);
		}
	});

	server.on("/update", HTTP_GET, [](AsyncWebServerRequest* request) {
		if (request->hasParam(HTTP_MOTOR_X) && request->hasParam(HTTP_MOTOR_Y)) {
			machine_room_update(request->getParam(HTTP_MOTOR_X)->value().toInt(),
			                    request->getParam(HTTP_MOTOR_Y)->value().toInt());
			request->send(200, "text/plain", "OK");
			return;
		}
		request->send(404, "text/plain");
	});

	server.on("/action", HTTP_GET, [](AsyncWebServerRequest* request){
		// Do something later on, need to add the hardware first.
		request->send(200, "text/plain", "OK");
		robot_flip();
	});

	server.onNotFound(notFound);
	server.begin();
}

void notFound(AsyncWebServerRequest* request)
{
	request->send(404, "text/plain", "Not found " + request->url());
}
