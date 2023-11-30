#include "transmitter.h"
#include "controls.h"


// REPLACE WITH THE MAC Address of your receiver
uint8_t recmac[]             = { 0x08, 0xB6, 0x1F, 0x29, 0x9A, 0x8C };
uint8_t transmac[]           = { 0x3C, 0x71, 0xBF, 0x9D, 0x9F, 0x88 };
unsigned long previousMillis = 0;
esp_now_data data;

bool is_connected = false;

void transmitter_begin()
{
	WiFi.mode(WIFI_MODE_STA);

	Serial.println(WiFi.macAddress());
	ESPNow.set_mac(transmac);
	WiFi.disconnect();
	ESPNow.init();
	ESPNow.add_peer(recmac);
	// ESPNow.reg_send_cb(OnDataSent);
}

void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status)
{
	Serial.print("\r\nLast Packet Send Status:\t");
	Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void transmitter_loop(void* v)
{
	(void)v;
	for (;;) {
		if (!is_connected) {
			vTaskDelay(100);
			continue;
		}

		int p = map(read_left_y(), 0, 4095, -100, 100);
		int r = map(read_right_x(), 0, 4095, -100, 100);
		p = constrain(p, -100, 100);
		r = constrain(r, -100, 100);
		if (abs(p) < 30) {
			p = 0;
		}
		if (abs(r) < 30) {
			r = 0;
		}

		if (p == data.pitch && r == data.roll) {
			// continue;
		}
		data.pitch = p;
		data.roll  = r;

		Serial.print(millis());
		Serial.print(": ");
		Serial.print(p);
		Serial.print(" - ");
		Serial.println(r);

		ESPNow.send_message(recmac, (uint8_t*)&data, sizeof(data));
		vTaskDelay(TRANSMITTER_INTERVAL / portTICK_RATE_MS);
	}
}
