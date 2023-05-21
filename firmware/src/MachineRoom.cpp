#include "MachineRoom.h"

MachineRoom::MachineRoom()
{
}

/// @brief Initializes the Machine Room (aka Wheels Controller)
/// @param leftMotorIN1 as digital enabled PWM forward pin
/// @param leftMotorIN2 as digital enabled PWM backward pin
/// @param rightMotorIN1 as digital enabled PWM forward pin
/// @param rightMotorIN2 as digital enabled PWM backward pin
MachineRoom::MachineRoom(
	uint8_t leftMotorIN1,
	uint8_t leftMotorIN2,
	uint8_t rightMotorIN1,
	uint8_t rightMotorIN2) :
	left(leftMotorIN1, leftMotorIN2),
	right(rightMotorIN1, rightMotorIN2)
{
	this->changeFriction(FRICTION_DEFAULT);
	this->changeSpeed(SPEED_DEFAULT);
	wasForward = false;
}

/// @brief Whenever the car needs to just go forward
/// @param pwm as an unsigned char from 0 to MOTOR_PWM_RANGE
void MachineRoom::forward(uint8_t pwm)
{
	if (!wasForward) {
		frictionCountdown = MOTOR_PWM_RANGE;
	}
	if (frictionStep < frictionCountdown) {
		frictionCountdown -= frictionStep;
	}
	else {
		frictionCountdown = 0;
	}
	wasForward = true;
	right.forward(pwm, frictionCountdown);
	left.forward(pwm, frictionCountdown);
}

/// @brief Whenever the car needs to just go backward
/// @param pwm as an unsigned char from 0 to MOTOR_PWM_RANGE
void MachineRoom::backward(uint8_t pwm)
{
	if (wasForward) {
		frictionCountdown = MOTOR_PWM_RANGE;
	}
	if (frictionStep < frictionCountdown) {
		frictionCountdown -= frictionStep;
	}
	else {
		frictionCountdown = 0;
	}
	wasForward = false;
	right.backward(pwm, frictionCountdown);
	left.backward(pwm, frictionCountdown);
}

/// @brief Whenever the car needs to break
/// @note Not quite sure this is the right way to do it: either pull-up or
/// pull-down.
void MachineRoom::brake()
{
	right.update(MOTOR_PWM_RANGE, MOTOR_PWM_RANGE);
	left.update(MOTOR_PWM_RANGE, MOTOR_PWM_RANGE);
}

void MachineRoom::update(int x, int y)
{
	// Whenever the joystick returns to zero, stop.
	// TODO: include a setting to disable this if necessary.
	if (x == 0 && y == 0) {
		this->brake();
		return;
	}

	// The Y axis informs us the power we should provide to the motors, whereas
	// the X axis informs us about the direction the car should go.
	double radian     = atan2(abs(y), abs(x));
	uint8_t module    = min(sqrt((double)pow(abs(y), 2) + pow(abs(x), 2)), (double)JOYSTICK_MASK);
	uint8_t pwmY      = module * sin(radian) * speed;
	// uint8_t pwmX      = module * cos(radian) * speed;
	uint8_t pwmModule = module * speed;

	// Whenever the X axis is below the motion threshold, the car should drive
	// straight.
	if (abs(x) < MOTOR_JOYSTICK_THRESHOLD) {
		y > 0 ? this->forward(pwmY) : this->backward(pwmY);
		return;
	}

	if (abs(y) < MOTOR_JOYSTICK_THRESHOLD) {
		return;
	}

	if (x > 0 && y > 0) {
		// 1st quadrant - forward and right.
		right.forward(pwmY, frictionCountdown);
		left.forward(pwmModule, frictionCountdown);
	}
	else if (x < 0 && y > 0) {
		// 2nd quadrant - forward and left.
		right.forward(pwmModule, frictionCountdown);
		left.forward(pwmY, frictionCountdown);
	}
	else if ((x < 0 && y < 0) || (x > 0 && y < 0)) {
		// 3rd quandrant - backward and left.
		right.backward(pwmModule, frictionCountdown);
		left.backward(pwmModule, frictionCountdown);
	}
}

/// @brief change friction to a proper step value
/// @param friction
void MachineRoom::changeFriction(uint8_t friction)
{
	this->frictionCountdown = MOTOR_PWM_RANGE;
	this->frictionStep      = MOTOR_PWM_RANGE / friction;
}

/// @brief change speed to a proper float value
/// @param speed
void MachineRoom::changeSpeed(uint8_t speed)
{
	this->speed = (float)speed / 100;
}
