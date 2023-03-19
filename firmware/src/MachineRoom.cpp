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
	uint8_t rightMotorIN2) :
	left(leftMotorIN1, leftMotorIN2),
	right(rightMotorIN1, rightMotorIN2)
{
#ifdef ESP8266
	// Only available on the ESP8266 Arduino Core
	analogWriteRange(MOTOR_PWM_RANGE);
#endif
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
	this->forward(50);
	delay(150);
	this->backwards(50);
	delay(150);
	this->brake();
}

/// @brief Whenever the car needs to just go forward
/// @param pwm as an unsigned char from 0 to 100
void MachineRoom::forward(uint8_t pwm)
{
	right.forward(pwm);
	left.forward(pwm);
}

/// @brief Whenever the car needs to just go backwards
/// @param pwm as an unsigned char from 0 to 100
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
	uint8_t absoluteY = abs(y) & MOTOR_MASK;             // Limited to 100;
	uint8_t absoluteX = abs(x) & MOTOR_MASK;             // Limited to 100;

	// Whenever the X axis is below the motion threshold, the car should drive
	// straight.
	if (absoluteX < MOTOR_JOYSTICK_THRESHOLD) {
		y > 0 ? this->forward(absoluteY) : this->backwards(absoluteY);
		return;
	}

	// We split the quadrant in two halfs using `absoluteY > absoluteX`.
	// First half is the one closer to the X axis and the second to the Y axis.
	int diff = absoluteY > absoluteX ? absoluteY - absoluteX : absoluteX - absoluteY;
	if (x > 0 && y > 0) {
		// 1st quadrant - forward and right.
		left.forward(absoluteY);
		absoluteY > absoluteX ? right.forward(diff) : right.reverse(diff);
	}
	else if (x < 0 && y > 0) {
		// 2nd quadrant - forward and left.
		right.forward(absoluteY);
		absoluteY > absoluteX ? left.forward(diff) : left.reverse(diff);
	}
	else if (x < 0 && y < 0) {
		// 3rd quandrant - backwards and left.
		right.reverse(absoluteY);
		absoluteY > absoluteX ? left.reverse(diff) : left.forward(diff);
	}
	else if (x > 0 && y < 0) {
		// 4th quadrant - backwards and right.
		left.reverse(absoluteY);
		absoluteY > absoluteX ? right.reverse(diff) : right.forward(diff);
	}
}
