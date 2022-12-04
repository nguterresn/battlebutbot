#include "MachineRoom.h"

MachineRoom::MachineRoom(
  uint8_t leftMotorIN1,
  uint8_t leftMotorIN2,
  uint8_t rightMotorIN1,
  uint8_t rightMotorIN2) : left(leftMotorIN1, leftMotorIN2), right(rightMotorIN1, rightMotorIN2) {}

// TODO: build motor driver
void MachineRoom::installLogger(Stream *serial) {
  this->serial = serial;
}

void MachineRoom::update(int x, int y) {
  int8_t backwards = ((uint32_t) y) >> 31;
  int8_t goingLeft = ((uint32_t) x) >> 31;
  uint8_t filteredY = y & (backwards ? MOTOR_BACKWARDS_MASK : MOTOR_FORWARD_MASK); // Limited to 100 and -100;
  uint8_t filteredX = x & (goingLeft ? MOTOR_BACKWARDS_MASK : MOTOR_FORWARD_MASK); // Limited to 100 and -100;

  if (filteredX < MOTOR_THRESHOLD) {
    filteredX = 0;
  }
  if (filteredY < MOTOR_THRESHOLD) {
    filteredY = 0;
  }

  uint8_t mappedY = map(filteredY, 0, 100, 0, 255);
  uint8_t mappedX = map(filteredX, 0, 100, 0, 255);

  // If forward
  if (backwards) {
    left.update(0, mappedX);
    right.update(mappedY, 0);
  } else {
    left.update(mappedX, 0);
    right.update(0, mappedY);
  }
  serial->print("sign: ");
  serial->print(backwards);
  serial->print(" direction: ");
  serial->println(mappedY);
}
