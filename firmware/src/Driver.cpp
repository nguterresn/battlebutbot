#include "Driver.h"

Driver::Driver() {}

Driver::Driver(uint8_t xIN1, uint8_t xIN2) {
  this->xIN1 = xIN1;
  this->xIN2 = xIN2;

  pinMode(this->xIN1, OUTPUT);
  pinMode(this->xIN2, OUTPUT);

  // should be in range from 0 to PWMRANGE, which is 255 by default.
  analogWrite(this->xIN1, 255);
  analogWrite(this->xIN2, 255);
}

void Driver::update(bool forward, uint8_t pwm) {
  if (forward) {
    analogWrite(this->xIN1, pwm);
    analogWrite(this->xIN2, 0);
  } else {
    analogWrite(this->xIN2, pwm);
    analogWrite(this->xIN1, 0);
  }
}
