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
	uint8_t servoPin,
	Stream* serial) :
	left(leftMotorIN1, leftMotorIN2),
	right(rightMotorIN1, rightMotorIN2),
	serial(serial)
{
	servo.attach(servoPin);
	servo.writeMicroseconds(DEFAULT_NEUTRAL_PULSE_WIDTH);
	isServoFlipped = false;

	this->changeFriction(FRICTION_DEFAULT);
	this->changeSpeed(SPEED_DEFAULT);
}

void MachineRoom::reset(void)
{
	this->brake();
	servo.writeMicroseconds(DEFAULT_NEUTRAL_PULSE_WIDTH);
	isServoFlipped = false;
}

/// @brief Whenever the car needs to just go forward
/// @param pwm as an unsigned char from 0 to MOTOR_PWM_RANGE
void MachineRoom::forward(uint8_t pwm)
{
	right.forward(pwm, 0);
	left.forward(pwm, 0);
}

/// @brief Whenever the car needs to just go backward
/// @param pwm as an unsigned char from 0 to MOTOR_PWM_RANGE
void MachineRoom::backward(uint8_t pwm)
{
	right.backward(pwm, 0);
	left.backward(pwm, 0);
}

/// @brief Whenever the car needs to break
/// @note Not quite sure this is the right way to do it: either pull-up or
/// pull-down.
void MachineRoom::brake(void)
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

	serial->print("x=");
	serial->print(x);
	serial->print("y=");
	serial->println(y);

	// The Y axis informs us the power we should provide to the motors, whereas
	// the X axis informs us about the direction the car should go.
	double radian     = atan2(abs(y), abs(x));
	uint8_t module    = min(sqrt((double)pow(abs(y), 2) + pow(abs(x), 2)), (double)JOYSTICK_MASK);
	uint8_t pwmModule = module * speedRatio;
	uint8_t pwmY      = pwmModule * sin(radian);
	// uint8_t pwmX      = module * cos(radian) * speed;

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
		right.forward(pwmModule, 0);
		left.forward(pwmY, 0);
	}
	else if (x < 0 && y > 0) {
		// 2nd quadrant - forward and left.
		right.forward(pwmY, 0);
		left.forward(pwmModule, 0);
	}
	else if (x < 0 && y < 0) {
		// 3rd & 4th quandrant - backwards.
		right.backward(pwmY, 0);
		left.backward(pwmModule, 0);
	}
	else if (x > 0 && y < 0) {
		right.backward(pwmModule, 0);
		left.backward(pwmY, 0);
	}
}

void MachineRoom::flip(void)
{
	servo.writeMicroseconds(isServoFlipped ? DEFAULT_NEUTRAL_PULSE_WIDTH : DEFAULT_MIN_PULSE_WIDTH);
	isServoFlipped = !isServoFlipped;
}

/// @brief change friction to a proper step value
/// @param friction
void MachineRoom::changeFriction(uint8_t friction)
{
	this->friction     = MOTOR_PWM_RANGE;
	this->frictionStep = MOTOR_PWM_RANGE / friction;
}

/// @brief change speed to a proper float value
/// @param speed
void MachineRoom::changeSpeed(uint8_t speed)
{
	this->speedRatio = (float)speed / 100.0;
}
