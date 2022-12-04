#include "MachineRoom.h"

MachineRoom::MachineRoom(
  uint8_t leftMotorIN1,
  uint8_t leftMotorIN2,
  uint8_t rightMotorIN1,
  uint8_t rightMotorIN2) : left(leftMotorIN1, leftMotorIN2), right(rightMotorIN1, rightMotorIN2) {
    analogWriteRange(MOTOR_PWM_RANGE);
  }

// TODO: build motor driver
void MachineRoom::installLogger(Stream *serial) {
  this->serial = serial;
}

void MachineRoom::update(int x, int y) {
  int8_t backwards = ((uint32_t) y) >> 31;
  // int8_t goingLeft = ((uint32_t) x) >> 31;
  uint8_t filteredY = abs(y) & MOTOR_FORWARD_MASK; // Limited to 100 and -100;
  uint8_t filteredX = abs(x) & MOTOR_FORWARD_MASK; // Limited to 100 and -100;
  if (filteredY > 100) {
    serial->println("Y is out of bounds!");
    return;
  }
  if (filteredX > 100) {
    serial->println("X is out of bounds!");
    return;
  }

  if (backwards) {
    left.update(0, filteredX);
    right.update(filteredY, 0);
  } else {
    left.update(filteredX, 0);
    right.update(0, filteredY);
  }
  serial->print("sign: ");
  serial->print(backwards);
  serial->print(" filterY: ");
  serial->print(filteredY);
  serial->print(" filterX: ");
  serial->println(filteredX);
}
