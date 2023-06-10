#include "WebServer.h"

AsyncWebServer server(80);

/// @brief Initialize ESP as a Access Point. Give it a SSID(name) and a custom DNS domain.
void setWifi()
{
	// Disable power saving on WiFi to improve responsiveness
	// (https://github.com/espressif/arduino-esp32/issues/1484)
	WiFi.setSleep(false);
	// Limit the amount of connections to the same web server.  One user per device.
	WiFi.softAP(SSID_OF_THE_NETWORK, NULL, 1, 0, 1);
	MDNS.begin(DNS_NETWORK_NAME);
	MDNS.addService("http", DNS_NETWORK_NAME, 80);
}

/// @brief Function to create all the endpoints and respective handlers for the WebServer.
void setWebServer(Robot& robot)
{
	server.on("/", HTTP_GET, [&robot](AsyncWebServerRequest* request) {
		if (request->hasParam(HTTP_CONFIG) &&
		    request->hasParam(HTTP_SPEED) &&
		    request->hasParam(HTTP_FRICTION)) {
			robot.saveConfiguration(request->getParam(HTTP_CONFIG)->value().toInt(),
			                        request->getParam(HTTP_SPEED)->value().toInt(),
			                        request->getParam(HTTP_FRICTION)->value().toInt());
		}
		else {
			robot.connect();
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

	server.on("/load-configuration", HTTP_GET, [&robot](AsyncWebServerRequest* request){
		char buffer[10] = { 0 };
		if (robot.serializeForRequest(buffer)) {
			request->send(200, "text/plain", buffer);
		}
	});

	server.on("/update", HTTP_GET, [&robot](AsyncWebServerRequest* request) {
		if (request->hasParam(HTTP_MOTOR_X) && request->hasParam(HTTP_MOTOR_Y)) {
			robot.oMachineRoom.update(
				request->getParam(HTTP_MOTOR_X)->value().toInt(),
				request->getParam(HTTP_MOTOR_Y)->value().toInt()
				);
			request->send(200, "text/plain", "OK");
			return;
		}
		request->send(404, "text/plain");
	});

	server.on("/action", HTTP_GET, [&robot](AsyncWebServerRequest* request){
		// Do something later on, need to add the hardware first.
		request->send(200, "text/plain", "OK");
		robot.oMachineRoom.flip();
	});

	server.onNotFound(notFound);
	server.begin();
}

void notFound(AsyncWebServerRequest* request)
{
	request->send(404, "text/plain", "Not found " + request->url());
}
