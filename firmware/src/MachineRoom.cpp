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
  int8_t goingLeft = ((uint32_t) x) >> 31;
  uint8_t filteredY = abs(y) & MOTOR_FORWARD_MASK; // Limited to 100 and -100;
  uint8_t filteredX = abs(x) & MOTOR_FORWARD_MASK; // Limited to 100 and -100;

  uint8_t motionLimit = 30;

  if (backwards) {
    if (filteredX < motionLimit) {
      left.reverse(filteredY);
      right.reverse(filteredY);
    } else if (filteredY > motionLimit) {
      if (goingLeft) {
        left.forward(filteredY);
        right.reverse(filteredX);
      } else {
        left.reverse(filteredX);
        right.forward(filteredY);
      }
    }
  } else {
    if (filteredX < motionLimit) {
      left.forward(filteredY);
      right.forward(filteredY);
    } else if (filteredY > motionLimit) {
      if (goingLeft) {
        left.reverse(filteredY);
        right.forward(filteredX);
      } else {
        left.forward(filteredX);
        right.reverse(filteredY);
      }
    }
  }
}
