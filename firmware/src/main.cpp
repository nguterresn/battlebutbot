#include <Arduino.h>
#include <NimBLEDevice.h>
#include "StateMachine.h"
#include "WebServer.h"

#define LED_FLASH 4
#define LED_ON_BOARD 33

#define BLUETOOTH_CORE 0
#define WIFI_CORE 1

#define SERIAL_ENABLED 1
#define BLUETOOTH_SCAN_TIME 5

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLEScan *pBLEScan;

// To be passed to Core 0
void _scanBluetooth();

unsigned char step = IDLE;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
  /*** Only a reference to the advertised device is passed now
    void onResult(BLEAdvertisedDevice advertisedDevice) { **/
  void onResult(BLEAdvertisedDevice *advertisedDevice)
  {
    if (advertisedDevice->haveName()) {
      #ifdef SERIAL_ENABLED
      Serial.print("Device name: ");
      Serial.println(advertisedDevice->getName().c_str());
      Serial.println("");
      #endif
    }

    if (advertisedDevice->haveServiceUUID()) {
      #ifdef SERIAL_ENABLED
      BLEUUID devUUID = advertisedDevice->getServiceUUID();
      Serial.print("Found ServiceUUID: ");
      Serial.println(devUUID.toString().c_str());
      Serial.println("");
      #endif
    }
  }
};

void _setupBluetooth() {
  BLEDevice::init("BLE Bitch!");
  // Setup Adv Server
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE
                                       );

  pCharacteristic->setValue("Hello World says Neil");
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  // Setup Scan!
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99); // less or equal setInterval value
}

void _scanBluetooth() {
  BLEScanResults foundDevices = pBLEScan->start(BLUETOOTH_SCAN_TIME, false);
  #ifdef SERIAL_ENABLED
  Serial.print("Devices found: ");
  Serial.println(foundDevices.getCount());
  // for (size_t i = 0; i < foundDevices.getCount(); i++)
  // {
  //   NimBLEAdvertisedDevice deviceFound = foundDevices.getDevice(i);
  //   Serial.println(deviceFound.getName().c_str());
  // }

  Serial.println("Scan done!");
  #endif
  pBLEScan->clearResults(); // delete results fromBLEScan buffer to release memory
}

void setup() {
  pinMode(33, OUTPUT);

  #ifdef SERIAL_ENABLED
  Serial.begin(9600);
  Serial.print("Just initialized...");
  #endif

  // to be passed to Core 1
  setWifi();
  setWebServer(step);

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
      break;
      break;
    case CONNECTED:
      break;

    default:
      // exit(0);
      break;
  }
}
