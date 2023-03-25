#include "MachineRoom.h"

/// @brief Initializes the Machine Room (aka Wheels Controller)
/// @param leftMotorIN1 as digital enabled PWM forward pin
/// @param leftMotorIN2 as digital enabled PWM reverse pin
/// @param rightMotorIN1 as digital enabled PWM forward pin
/// @param rightMotorIN2 as digital enabled PWM reverse pin
MachineRoom::MachineRoom(
	uint8_t leftMotorIN1,
	uint8_t leftMotorIN2,
	uint8_t rightMotorIN1,
	uint8_t rightMotorIN2,
	uint8_t feedbackLed) :
	left(leftMotorIN1, leftMotorIN2),
	right(rightMotorIN1, rightMotorIN2),
	ledPin(feedbackLed)
{
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);
}

/// @brief Store the stream object so it can be used to debug code
/// whenever needed.
/// @param serial Serial object of stream type
void MachineRoom::installLogger(Stream* serial)
{
	this->serial = serial;
}

void MachineRoom::connect()
{
	// Add an LED to show the web control page is open.
	this->brake();
	digitalWrite(ledPin, HIGH);
}

/// @brief Whenever the car needs to just go forward
/// @param pwm as an unsigned char from 0 to MOTOR_PWM_RANGE
void MachineRoom::forward(uint8_t pwm)
{
	right.forward(pwm);
	left.forward(pwm);
}

/// @brief Whenever the car needs to just go backwards
/// @param pwm as an unsigned char from 0 to MOTOR_PWM_RANGE
void MachineRoom::backwards(uint8_t pwm)
{
	right.reverse(pwm);
	left.reverse(pwm);
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
		y > 0 ? this->forward(pwmY) : this->backwards(pwmY);
		return;
	}

	if (abs(y) < MOTOR_JOYSTICK_THRESHOLD) {
		return;
	}

	if (x > 0 && y > 0) {
		// 1st quadrant - forward and right.
		right.forward(pwmY);
		left.forward(pwmModule);
	}
	else if (x < 0 && y > 0) {
		// 2nd quadrant - forward and left.
		right.forward((pwmModule));
		left.forward(pwmY);
	}
	else if ((x < 0 && y < 0) || (x > 0 && y < 0)) {
		// 3rd quandrant - backwards and left.
		right.reverse(pwmModule);
		left.reverse(pwmModule);
	}
}
