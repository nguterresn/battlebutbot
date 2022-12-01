#include "Motor.h"

// TODO: build motor driver
void Motor::installLogger(Stream *serial) {
  this->serial = serial;
}

void Motor::update(unsigned char x, unsigned char y) {
  serial->print("X: ");
  serial->print(x);
  serial->print(" Y: ");
  serial->println(y);
  return;
}
