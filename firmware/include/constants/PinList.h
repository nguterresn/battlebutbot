#ifdef ESP32
#define LEFT1          16
#define LEFT2          17
#define RIGHT1         18
#define RIGHT2         19

#define SERVO          21
// ADC2 pins cannot be used when Wi-Fi is used.
#define BATTERY_SENSOR ADC1_CH6 // GPIO 36
#define FEEDBACK_LED   22
#elif ESP8266
#define LEFT1          D1
#define LEFT2          D2
#define RIGHT1         D5
#define RIGHT2         D4

#define SERVO          D6
#define BATTERY_SENSOR A0
#define FEEDBACK_LED   D7
#endif
