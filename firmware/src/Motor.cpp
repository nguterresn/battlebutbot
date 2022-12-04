#include "Motor.h"

Motor::Motor() {}

Motor::Motor(uint8_t xIN1, uint8_t xIN2) {
  this->xIN1 = xIN1;
  this->xIN2 = xIN2;

  pinMode(this->xIN1, OUTPUT);
  pinMode(this->xIN2, OUTPUT);

  // should be in range from 0 to PWMRANGE, which is 255 by default.
  analogWrite(this->xIN1, MOTOR_PWM_RANGE);
  analogWrite(this->xIN2, MOTOR_PWM_RANGE);
}

void Motor::update(uint8_t xIN1pwm, uint8_t xIN2pwm) {
  analogWrite(this->xIN1, xIN1pwm);
  analogWrite(this->xIN2, xIN2pwm);
}
