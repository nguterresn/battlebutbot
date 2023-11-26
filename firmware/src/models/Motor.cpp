#include "models/Motor.h"

// To improve brushed motors:
// https://learn.adafruit.com/improve-brushed-dc-motor-performance?view=all
/**
 * @brief Construct a new Motor:: Motor object
 *
 * @param xIN1 as a pin
 * @param xIN2 as a pin
 */
Motor::Motor(uint8_t xIN1, uint8_t xIN2, uint8_t drift) : xIN1(xIN1), xIN2(xIN2)
{
	pinMode(this->xIN1, OUTPUT);
	pinMode(this->xIN2, OUTPUT);

	// should be in range from 0 to PWMRANGE, which is 255 by default.
	analogWrite(this->xIN1, MOTOR_PWM_RANGE);
	analogWrite(this->xIN2, MOTOR_PWM_RANGE);

	update(drift);
}

/**
 * @brief Update motor pwm pins (slow decay)
 *
 * @param xIN1pwm
 * @param xIN2pwm
 */
void Motor::update(uint8_t xIN1pwm, uint8_t xIN2pwm)
{
	analogWrite(this->xIN1, xIN1pwm);
	analogWrite(this->xIN2, xIN2pwm);
}

/**
 * @brief Update drift ratio. 0 means max drift. 1 means no drift.
 *
 * @param drift as a value between 0 and 100.
 */
void Motor::update(uint8_t drift)
{
	this->driftRatio = (float)drift / 100.0;
}

void Motor::brake(void)
{
	this->update(MOTOR_PWM_RANGE, MOTOR_PWM_RANGE);
}

/**
 * @brief Motor goes forward based on how big is the pwm argument (slow decay).
 *
 * @param pwm as a 8bit value, 0 is max speed
 */
void Motor::forward(uint8_t pwm)
{
#ifdef HIGH_PERFORMANCE
	this->update(MOTOR_PWM_RANGE, MOTOR_PWM_RANGE - pwm * driftRatio);
#elif LOW_POWER
	this->update(pwm * driftRatio, 0);
#endif
}

/**
 * @brief Motor goes backwards based on how big is the pwm argument (slow decay).
 *
 * @param pwm as a 8bit value, 0 is max speed
 */
void Motor::backward(uint8_t pwm)
{
#ifdef HIGH_PERFORMANCE
	this->update(MOTOR_PWM_RANGE - pwm * driftRatio, MOTOR_PWM_RANGE);
#elif LOW_POWER
	this->update(0, pwm * driftRatio);
#endif
}
