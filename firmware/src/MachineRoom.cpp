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
  uint8_t backwards = ((uint32_t) y) >> 31;
  uint8_t goingLeft = ((uint32_t) x) >> 31;
  uint8_t filteredY = abs(y) & MOTOR_MASK; // Limited to 100;
  uint8_t filteredX = abs(x) & MOTOR_MASK; // Limited to 100;

  uint8_t motionLimit = MOTOR_JOYSTICK_THRESHOLD;

  if (backwards) {
    if (filteredX < motionLimit) {
      left.reverse(filteredY);
      right.reverse(filteredY);
    } else if (filteredY > motionLimit) {
      if (goingLeft) {
        // Turning left.
        int mappedLeft = filteredY - filteredX;
        right.reverse(filteredY);
        mappedLeft > 0 ? left.reverse(abs(mappedLeft)) : left.forward(abs(mappedLeft));
      } else {
        // Turning right.
        int mappedRight = filteredY + filteredX;
        left.reverse(filteredY);
        mappedRight > 0 ? left.reverse(abs(mappedRight)) : left.reverse(abs(mappedRight));
      }
    }
  } else {
    // Car is going forward.
    if (filteredX < motionLimit) {
      left.forward(filteredY);
      right.forward(filteredY);
    } else if (filteredY > motionLimit) {
      if (goingLeft) {
        // Turning left.
        int mappedLeft = filteredY + filteredX;
        right.forward(filteredY);
        mappedLeft > 0 ? left.forward(abs(mappedLeft)) : left.reverse(abs(mappedLeft));
      } else {
        // Turning right.
        int mappedRight = filteredY - filteredX;
        left.forward(filteredY);
        mappedRight > 0 ? right.forward(abs(mappedRight)) : right.reverse(abs(mappedRight));
      }
    }
  }
}
