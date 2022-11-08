#include <Arduino.h>
#include <map>
#include <BluetoothSerial.h>
#include "StateMachine.h"
#include "WebServer.h"

#define LED_FLASH 4
#define LED_ON_BOARD 33

#define BLUETOOTH_CORE 0
#define WIFI_CORE 1

#define SERIAL_ENABLED 1
#define BLUETOOTH_SCAN_TIME 5

#define BT_DISCOVER_TIME  3000 // 3 seconds
#define BT_SCAN_LIMIT  10 // 10 devices

BluetoothSerial BTnow;

esp_spp_sec_t sec_mask=ESP_SPP_SEC_NONE; // or ESP_SPP_SEC_ENCRYPT|ESP_SPP_SEC_AUTHENTICATE to request pincode confirmation
esp_spp_role_t role=ESP_SPP_ROLE_SLAVE; // or ESP_SPP_ROLE_MASTER

unsigned char step = IDLE;
String bluetoothDeviceConnected;

struct ScanResult {
  char *result[BT_SCAN_LIMIT];
  int counter;
};

struct ScanResult scanResult;

void btAdvertisedDeviceFound(BTAdvertisedDevice* pDevice) {
  if (pDevice->haveName()) {
    scanResult.result[scanResult.counter] = strcpy((char*) malloc(20), pDevice->getName().c_str());
    Serial.printf("Found a device asynchronously2 : %s\n", scanResult.result[scanResult.counter]);
    // Send an event to populate web server listed devices
    sendEvent(EVENT_SEND_SCANNED_DEVICE, scanResult.result[scanResult.counter]);
    // Increase counter.
    scanResult.counter++;
  }
}

void _setupBluetooth() {
  if(!BTnow.begin("ESP32test", true) ) {
    Serial.println("========== BTnow failed!");
    abort();
  }
}

void _scanBluetooth() {
  Serial.print("Starting discoverAsync...");
  // Clean the previous BT scan results.
  scanResult.counter = 0;
  // Start discovery
  if (BTnow.discoverAsync(btAdvertisedDeviceFound)) {
    Serial.println("Findings will be reported in \"btAdvertisedDeviceFound\"");
    delay(BT_DISCOVER_TIME);
    Serial.print("Stopping discoverAsync... ");
    BTnow.discoverAsyncStop();
    Serial.println("stopped");
  } else {
    Serial.println("Error on discoverAsync f.e. not workin after a \"connect\"");
  }
}

void _connectBluetooth() {
  Serial.println("Device name to be connected: ");
  Serial.println(bluetoothDeviceConnected.c_str());
  // _scanBluetooth();
  if (BTnow.connect(bluetoothDeviceConnected)) {
    Serial.println("Device connected!");
  }
}

void setup() {
  pinMode(33, OUTPUT);

  #ifdef SERIAL_ENABLED
  Serial.begin(9600);
  Serial.print("Just initialized...");
  #endif

  // to be passed to Core 1
  setWifi();
  setWebServer(step, bluetoothDeviceConnected);

  _setupBluetooth();
}

void loop() {
  switch (step) {
    case IDLE:
      break;
    case SCAN_BLUETOOTH:
      _scanBluetooth();
      step = IDLE;
      break;
    case CONNECT_BLUETOOTH:
      _connectBluetooth();
      step = IDLE;
      break;
    case CONNECTED:
      break;

    default:
      // exit(0);
      break;
  }
}
