#ifndef PIN_LIST_H_
#define PIN_LIST_H_

// List of GPIOs
// Note: ADC2 pins cannot be used when Wi-Fi is used.

#define MOTOR_LEFT1            11
#define MOTOR_LEFT2            38
#define MOTOR_RIGHT1           9
#define MOTOR_RIGHT2           10
#define MOTOR_FAULT            12

#define SERVO_BACK             17
#define SERVO_FRONT            18

#define PROXIMITY_SENSOR_RIGHT 6
#define PROXIMITY_SENSOR_LEFT  7

#define BATTERY_SENSOR         1
#define FEEDBACK_LED           13
#define BUZZER                 2

#define ACC_SDA                47
#define ACC_SCL                48
#define ACC_INT1               14
#define ACC_INT2               21

#endif /* PIN_LIST_H_ */
