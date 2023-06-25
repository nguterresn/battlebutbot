#include "ServoMotor.h"

/**
 * @brief Construct a new Servo Motor:: Servo Motor object
 *
 * @param pin as pin the servo
 */
ServoMotor::ServoMotor(uint8_t pin)
{
	enabled = false;
	_servo.attach(pin, MIN_ANGLE_IN_US, MAX_ANGLE_IN_US);
	_servo.writeMicroseconds(NEG_90_ANGLE_IN_US);
}

/**
 * @brief Toggle the servo enable variable
 *
 * @param enable
 */
void ServoMotor::update(bool enable)
{
	this->enabled = enable;
}

/**
 * @brief Reset the servo to its initial state/angle.
 *
 */
void ServoMotor::reset(void)
{
	_servo.writeMicroseconds(NEG_90_ANGLE_IN_US);
	flipped = false;
}

/**
 * @brief Flip the servo motor.
 *
 */
void ServoMotor::flip(void)
{
	if (!enabled) {
		return;
	}
	_servo.writeMicroseconds(isFlipped() ? _0_ANGLE_IN_US : NEG_90_ANGLE_IN_US);
	flipped = !flipped;
}

bool ServoMotor::isFlipped(void)
{
	return flipped == true;
}
