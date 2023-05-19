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
	uint8_t rightMotorIN2,
	uint8_t step) :
	left(leftMotorIN1, leftMotorIN2),
	right(rightMotorIN1, rightMotorIN2),
	step(step)
{
}

/// @brief Whenever the car needs to just go forward
/// @param pwm as an unsigned char from 0 to MOTOR_PWM_RANGE
void MachineRoom::forward(uint8_t pwm)
{
	if (!wasForward) {
		friction = MOTOR_PWM_RANGE;
	}
	if (step < friction) {
		friction -= step;
	}
	else {
		friction = 0;
	}
	wasForward = true;
	right.forward(pwm, friction);
	left.forward(pwm, friction);
}

/// @brief Whenever the car needs to just go backward
/// @param pwm as an unsigned char from 0 to MOTOR_PWM_RANGE
void MachineRoom::backward(uint8_t pwm)
{
	if (wasForward) {
		friction = MOTOR_PWM_RANGE;
	}
	if (step < friction) {
		friction -= step;
	}
	else {
		friction = 0;
	}
	wasForward = false;
	right.backward(pwm, friction);
	left.backward(pwm, friction);
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
	uint8_t module    = min(sqrt((float)pow(abs(y), 2) + pow(abs(x), 2)), (double)JOYSTICK_MASK);
	uint8_t pwmY      = module * sin(radian) * 2.55;
	// uint8_t pwmX      = module * cos(radian) * 2.55;
	uint8_t pwmModule = module * 2.55;

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
		right.forward(pwmY, friction);
		left.forward(pwmModule, friction);
	}
	else if (x < 0 && y > 0) {
		// 2nd quadrant - forward and left.
		right.forward(pwmModule, friction);
		left.forward(pwmY, friction);
	}
	else if ((x < 0 && y < 0) || (x > 0 && y < 0)) {
		// 3rd quandrant - backward and left.
		right.backward(pwmModule, friction);
		left.backward(pwmModule, friction);
	}
}

// void MachineRoom::changeLeftMotorFriction(uint8_t step)
// {
// 	left.step = step;
// }

// void MachineRoom::changeRightMotorFriction(uint8_t step)
// {
// 	right.step = step;
// }
