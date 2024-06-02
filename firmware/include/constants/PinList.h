#ifndef PIN_LIST_H_
#define PIN_LIST_H_

// Pins for the ESP32 S3:
// https://www.espressif.com/sites/default/files/documentation/esp32-s3-wroom-1_wroom-1u_datasheet_en.pdf

// List of GPIOs
// Note: ADC2 pins cannot be used when Wi-Fi is used.

#define MOTOR_LEFT1    39
#define MOTOR_LEFT2    38
#define MOTOR_RIGHT1   41
#define MOTOR_RIGHT2   40
#define MOTOR_FAULT    42

#endif /* PIN_LIST_H_ */
