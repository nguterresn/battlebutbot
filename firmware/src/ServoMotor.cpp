#include "ServoMotor.h"

ServoMotor::ServoMotor(uint8_t pin)
{
	_servo.attach(pin, MIN_ANGLE_IN_US, MAX_ANGLE_IN_US, NEG_90_ANGLE_IN_US);
}

void ServoMotor::reset(void) {
	_servo.writeMicroseconds(NEG_90_ANGLE_IN_US);
	isFlipped = false;
}

void ServoMotor::flip(void) {
  _servo.writeMicroseconds(isFlipped ? _0_ANGLE_IN_US : NEG_90_ANGLE_IN_US);
	isFlipped = !isFlipped;
}
