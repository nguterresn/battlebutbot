
// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
// #include "I2Cdev.h"

// #include "MPU6050_6Axis_MotionApps20.h"
// #include "Wire.h"

#include <Arduino.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif ESP32
#include <WiFi.h>
#endif
#include "ESPNowW.h"


// #define TRANSMITTER
#define RECEIVER
// #define MPU


#ifdef TRANSMITTER
#define JOYSTICK
#endif
#define POT_X 35
#define POT_Y 34

#define TRANSMITTER_INTERVAL 30

// REPLACE WITH THE MAC Address of your receiver 
uint8_t recmac[] = {0x08,0xB6,0x1F,0x29,0x9A,0x8C};
uint8_t transmac[] = {0x3C,0x71,0xBF,0x9D,0x9F,0x88};


#ifdef MPU

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 mpu;

#define OUTPUT_READABLE_YAWPITCHROLL
// #define OUTPUT_READABLE_WORLDACCEL


// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer


// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

#define INTERRUPT_PIN 15 // use pin 15 on ESP8266

const char DEVICE_NAME[] = "mpu6050";


volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void ICACHE_RAM_ATTR dmpDataReady() {
    mpuInterrupt = true;
}
#endif

// Updates DHT readings every 10 seconds
unsigned long previousMillis = 0;    // will store last time DHT was updated 

// Variable to store if sending data was successful
String success;

//Structure example to send data
//Must match the receiver structure
typedef struct esp_now_data {
    int roll;
    int pitch;
} esp_now_data;

// Create a struct_message called DHTReadings to hold sensor readings
esp_now_data foo;

// Create a struct_message to hold incoming sensor readings
esp_now_data incomingFoo;


void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

void OnDataRecv(const uint8_t *mac_addr,const uint8_t *data, int data_len);

#ifdef MPU
void mpu_setup()
{
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();
  Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties


  // initialize device
  Serial.println(F("Initializing I2C devices..."));
  mpu.initialize();
  pinMode(INTERRUPT_PIN, INPUT);

  // verify connection
  Serial.println(F("Testing device connections..."));
  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

  // load and configure the DMP
  Serial.println(F("Initializing DMP..."));
  devStatus = mpu.dmpInitialize();

  // supply your own gyro offsets here, scaled for min sensitivity
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
    // turn on the DMP, now that it's ready
    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);

    // enable Arduino interrupt detection
    Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();

    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    Serial.println(F("DMP ready! Waiting for first interrupt..."));
    dmpReady = true;

    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }
}
#endif


esp_now_peer_info_t peerInfo;


void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  Serial.println("starting..");
#ifdef ESP8266
    WiFi.mode(WIFI_STA); // MUST NOT BE WIFI_MODE_NULL
#elif ESP32
    WiFi.mode(WIFI_MODE_STA);
#endif
    Serial.println(WiFi.macAddress());
    // TODO get set_mac function to work.
    #ifdef TRANSMITTER
    ESPNow.set_mac(transmac);
    // wifi_set_macaddr(STATION_IF, mac);
    #else
    // ESPNow.set_mac(recmac);
    #endif
    WiFi.disconnect();
    ESPNow.init();
    #ifdef RECEIVER
    ESPNow.add_peer(transmac);
    ESPNow.reg_recv_cb(OnDataRecv);
    #else
    ESPNow.add_peer(recmac);
    // ESPNow.reg_send_cb(OnDataSent);
    #endif

  // Init ESP-NOW
  // if (esp_now_init() != 0) {
  //   Serial.println("Error initializing ESP-NOW");
  //   return;
  // }

  // esp_now_set

  // Set ESP-NOW Role
  // esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

  // // Once ESPNow is successfully Init, we will register for Send CB to
  // // get the status of Trasnmitted packet
  // esp_now_register_send_cb(OnDataSent);
  
  // memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  // peerInfo.channel = 0;  
  // peerInfo.encrypt = false;
  
  // // Add peer        
  // if (esp_now_add_peer(&peerInfo) != ESP_OK){
  //   Serial.println("Failed to add peer");
  //   return;
  // }

  // Register peer
  // esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  
  // // Register for a callback function that will be called when data is received
  // esp_now_register_recv_cb(OnDataRecv);

  #ifdef MPU
  mpu_setup();
  #endif


  #ifdef JOYSTICK
  pinMode(POT_X, INPUT); 
  pinMode(POT_Y, INPUT); 
  #endif
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

 // Callback when data is received
void OnDataRecv(const uint8_t *mac_addr,const uint8_t *data, int data_len) {
  memcpy(&incomingFoo, data, sizeof(incomingFoo));

  Serial.print(incomingFoo.pitch);
  Serial.print(" : ");
  Serial.println(incomingFoo.roll);
  Serial.print("\t");
}


  #ifdef MPU

void mpu_loop()
{
  // if programming failed, don't try to do anything
  if (!dmpReady) return;

  // wait for MPU interrupt or extra packet(s) available
  if (!mpuInterrupt && fifoCount < packetSize) return;

  // reset interrupt flag and get INT_STATUS byte
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();

  // get current FIFO count
  fifoCount = mpu.getFIFOCount();

  // check for overflow (this should never happen unless our code is too inefficient)
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    // reset so we can continue cleanly
    mpu.resetFIFO();
    Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
  } else if (mpuIntStatus & 0x02) {
    // wait for correct available data length, should be a VERY short wait
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

    // read a packet from FIFO
    mpu.getFIFOBytes(fifoBuffer, packetSize);

    // track FIFO count here in case there is > 1 packet available
    // (this lets us immediately read more without waiting for an interrupt)
    fifoCount -= packetSize;

#ifdef OUTPUT_READABLE_YAWPITCHROLL
    // display Euler angles in degrees
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    // Serial.print("ypr\t");
    // // Serial.print(ypr[0] * 180/M_PI);
    // // Serial.print("\t");
    // Serial.print(ypr[1] * 180/M_PI);
    // Serial.print("\t");
    // Serial.println(ypr[2] * 180/M_PI);

    int p = map((int) (ypr[1] * 180/M_PI), -30, 30, -100, 100);
    int r = map((int) (ypr[2] * 180/M_PI), -30, 30, -100, 100);
    p = constrain(p, -100, 100);
    r = constrain(r, -100, 100);
    if (abs(p) < 30) p = 0;
    if (abs(r) < 30) r = 0;

    foo.pitch = p;
    foo.roll = r;
    Serial.print("pr\t");
    Serial.print(foo.pitch);
    Serial.print("\t");
    Serial.println(foo.roll);
    esp_now_send(broadcastAddress, (uint8_t *) &foo, sizeof(foo));
#endif

  }
}
  #endif
void loop() {
  #ifdef TRANSMITTER
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= TRANSMITTER_INTERVAL) {
    // save the last time you updated the DHT values
    previousMillis = currentMillis;
    #ifdef MPU
    mpu_loop();
    #endif

    int p = map(analogRead(POT_Y), 0, 4095, -100, 100);
    int r = map(analogRead(POT_X), 0, 4095, -100, 100);
    p = constrain(p, -100, 100);
    r = constrain(r, -100, 100);
    if (abs(p) < 30) p = 0;
    if (abs(r) < 30) r = 0;

    Serial.println(p);
    Serial.println(r);

    foo.pitch = p;
    foo.roll = r;

    ESPNow.send_message(recmac, (uint8_t *) &foo, sizeof(foo));
  }
  #endif
}

