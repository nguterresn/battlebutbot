#ifndef MOTOR_SETTINGS_H_
#define MOTOR_SETTINGS_H_

#define MOTOR_PWM_FREQUENCY  200  // 200Hz
#define MOTOR_PWM_RESOLUTION 8    // 8 bits
#define MOTOR_PWM_RANGE      255

#define MOTOR_RIGHT1_CHANNEL 4
#define MOTOR_RIGHT2_CHANNEL 5
#define MOTOR_LEFT1_CHANNEL  6
#define MOTOR_LEFT2_CHANNEL  7

#define MOTOR_SPEED_DEFAULT  MOTOR_PWM_RANGE        // Descending speed (255 -> 1)

#endif /* MOTOR_SETTINGS_H_ */
