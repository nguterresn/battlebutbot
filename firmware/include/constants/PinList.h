#ifndef PIN_LIST_H_
#define PIN_LIST_H_

// Pins for the ESP32 S1:
// https://randomnerdtutorials.com/esp32-pinout-reference-gpios/

// List of GPIOs
// Note: ADC2 pins cannot be used when Wi-Fi is used.

#ifdef S1
#define MOTOR_LEFT1    16
#define MOTOR_LEFT2    17
#define MOTOR_RIGHT1   22
#define MOTOR_RIGHT2   23
#elif S2
#error "Motor pins are missing for the ESP32 S2"
#elif S3
#define MOTOR_RIGHT1   11
#define MOTOR_RIGHT2   38
#define MOTOR_LEFT1    10
#define MOTOR_LEFT2    9
#endif
#define MOTOR_FAULT    12

#define BATTERY_SENSOR 1
#define FEEDBACK_LED   13

#define ACC_SDA        47
#define ACC_SCL        48
#define ACC_INT1       14
#define ACC_INT2       21

#endif /* PIN_LIST_H_ */
