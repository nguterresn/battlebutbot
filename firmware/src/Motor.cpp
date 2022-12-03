#include "Motor.h"

Motor::Motor(uint8_t xIN1, uint8_t xIN2) : driver(xIN1, xIN2) {}

// TODO: build motor driver
void Motor::installLogger(Stream *serial) {
  this->serial = serial;
}

void Motor::update(int x, int y) {
  uint32_t sign = x & ((1 << 32) - 1);
  int8_t direction = y & MOTOR_VALUE_MASK; // Limited to 100 and -100;
  // int8_t way = x & MOTOR_VALUE_MASK; // Limited to 100 and -100;
  driver.update(sign, direction);
  serial->print("sign: ");
  serial->print(sign);
  serial->print(" direction: ");
  serial->println(direction);
  // serial->print(" Y: ");
  // serial->println(y);
}
