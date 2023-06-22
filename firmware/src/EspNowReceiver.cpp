#include "EspNowReceiver.h"

esp_now_data recEspNowData;

void initEspNow() {
	Serial.println(F("\nInitializing Esp Now.")); Serial.println();
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
	Serial.print(F("Wifi Mac: "));
  Serial.println(WiFi.macAddress());
  WiFi.disconnect();

	// Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Set ESP-NOW Role
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);

  // // Once ESPNow is successfully Init, we will register for Send CB to
  // // get the status of Trasnmitted packet
  // esp_now_register_send_cb(OnDataSent);
  
  // // Register peer
  // esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  
  // // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);

  robot.oMachineRoom.changeSpeed(100);
}

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  if (len < sizeof(recEspNowData)) {
    // error
  }
  memcpy(&recEspNowData, incomingData, sizeof(recEspNowData));
  // Serial.print("pr\t");
  // Serial.print(recEspNowData.pitch);
  // Serial.print("\t");
  // Serial.println(recEspNowData.roll);
  // Serial.flush();
  // Handle data received.
  robot.oMachineRoom.update(recEspNowData.pitch, recEspNowData.roll);
}