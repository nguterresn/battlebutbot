#include "models/ServoMotor.h"

/**
 * @brief Construct a new Servo Motor:: Servo Motor object
 *
 * @param pin as pin the servo
 */
ServoMotor::ServoMotor(uint8_t pin)
{
	_servo.attach(pin, MIN_ANGLE_IN_US, MAX_ANGLE_IN_US, NEG_90_ANGLE_IN_US);
}

/**
 * @brief Reset the servo to its initial state/angle.
 *
 */
void ServoMotor::reset(void)
{
	_servo.writeMicroseconds(NEG_90_ANGLE_IN_US);
	isFlipped = false;
}

/**
 * @brief Flip the servo motor.
 *
 */
void ServoMotor::flip(void)
{
	_servo.writeMicroseconds(isFlipped ? _0_ANGLE_IN_US : NEG_90_ANGLE_IN_US);
	isFlipped = !isFlipped;
}
