#include "Motor.h"

/**
 * @brief Construct a new Motor:: Motor object
 *
 * @param xIN1 as a pin
 * @param xIN2 as a pin
 */
Motor::Motor(uint8_t xIN1, uint8_t xIN2) : xIN1(xIN1), xIN2(xIN2)
{
	pinMode(this->xIN1, OUTPUT);
	pinMode(this->xIN2, OUTPUT);

	// should be in range from 0 to PWMRANGE, which is 255 by default.
	analogWrite(this->xIN1, MOTOR_PWM_RANGE);
	analogWrite(this->xIN2, MOTOR_PWM_RANGE);
}

/**
 * @brief Update motor pwm pins
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
 * @brief Motor goes forward based on how big is the pwm argument.
 *
 * @param pwm
 * @param friction not being used atm, default is 0.
 */
void Motor::forward(uint8_t pwm, uint8_t friction)
{
	this->update(pwm, friction);
}

/**
 * @brief Motor goes backwards based on how big is the pwm argument.
 *
 * @param pwm
 * @param friction not being used atm, default is 0.
 */
void Motor::backward(uint8_t pwm, uint8_t friction)
{
	this->update(friction, pwm);
}
