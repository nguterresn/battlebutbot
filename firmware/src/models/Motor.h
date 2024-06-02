#ifndef MOTOR_H_
#define MOTOR_H_

#include <Arduino.h>

#define MOTOR_JOYSTICK_DEAD_ZONE 15

// Choose the type of motor decay
// Note: low power mode is not working atm.
// #define LOW_POWER                // fast decay
#define HIGH_PERFORMANCE         // slow decay

class Motor {
public:
  Motor(uint8_t xIN1_pin, uint8_t xIN2_pin, uint8_t xIN1_channel, uint8_t xIN2_channel);
  void move(uint8_t xIN1pwm, uint8_t xIN2pwm);
  void brake(void);
  void forward(uint8_t pwm);
  void backward(uint8_t pwm);
private:
  uint8_t xIN1_channel, xIN2_channel;
};

#endif /* MOTOR_H_ */
