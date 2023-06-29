#include "ServoMotor.h"

/**
 * @brief Construct a new Servo Motor:: Servo Motor object
 *
 * @param pin as pin the servo
 */
ServoMotor::ServoMotor(uint8_t pin)
{
	enabled   = false;
	this->min = MIN_ANGLE_IN_US;
	this->max = MAX_ANGLE_IN_US;
	ledcSetup(SERVO_CHANNEL, PWM_DEFAULT_FREQUENCY, PWM_DEFAULT_RESOLUTION);
	ledcAttachPin(pin, SERVO_CHANNEL);
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
	write(MIN_ANGLE_IN_US);
	flipped = false;
}

void ServoMotor::write(uint32_t usec)
{
	usec = min(usec, this->max);
	usec = max(usec, this->min);
	uint32_t value = ((pow(2, PWM_DEFAULT_RESOLUTION) - 1) / this->max) * usec;
	ledcWrite(SERVO_CHANNEL, value);
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
	// Note: The SG90 is supposed to go up to 2000ms period (90'), but for some reason
	// the one I'm using only goes up to 1500ms (0').
	write(isFlipped() ? _0_ANGLE_IN_US : MIN_ANGLE_IN_US);
	flipped = !flipped;
}

bool ServoMotor::isFlipped(void)
{
	return flipped == true;
}
