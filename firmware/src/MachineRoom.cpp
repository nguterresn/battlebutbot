#include "MachineRoom.h"

/**
 * @brief Construct a new Machine Room:: Machine Room object
 *
 * @param serial optional reference to Arduino's Serial library
 */
MachineRoom::MachineRoom(Stream* serial) :
	left(LEFT1, LEFT2),
	right(RIGHT1, RIGHT2),
	servo(SERVO),
	serial(serial)
{
	pinMode(FEEDBACK_LED, OUTPUT);

	this->changeFriction(FRICTION_DEFAULT);
	this->changeSpeed(SPEED_DEFAULT);
}

/**
 * @brief Resets machine room by stopping the motors or returning them to initial position.
 *
 */
void MachineRoom::reset(void)
{
	this->brake();
	servo.reset();
}

/**
 * @brief Whenever the car needs to just go forward
 *
 * @param pwm as an unsigned char from 0 to MOTOR_PWM_RANGE
 */
void MachineRoom::forward(uint8_t pwm)
{
	right.forward(pwm, 0);
	left.forward(pwm, 0);
}

/**
 * @brief Whenever the car needs to just go backward
 *
 * @param pwm as an unsigned char from 0 to MOTOR_PWM_RANGE
 */
void MachineRoom::backward(uint8_t pwm)
{
	right.backward(pwm, 0);
	left.backward(pwm, 0);
}

/**
 * @brief Whenever the car needs to break
 *
 */
void MachineRoom::brake(void)
{
	right.update(MOTOR_PWM_RANGE, MOTOR_PWM_RANGE);
	left.update(MOTOR_PWM_RANGE, MOTOR_PWM_RANGE);
}

/**
 * @brief Update motors according to web's joystick incoming data.
 *
 * @param x incoming x axis integer from web's joystick.
 * @param y incoming y axis integer from web's joystick.
 */
void MachineRoom::update(int x, int y)
{
	// Whenever the joystick returns to zero, stop.
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
		right.forward(pwmY, 0);
		left.forward(pwmModule, 0);
	}
	else if (x < 0 && y > 0) {
		// 2nd quadrant - forward and left.
		right.forward(pwmModule, 0);
		left.forward(pwmY, 0);
	}
	else if (x < 0 && y < 0) {
		// 3rd & 4th quandrant - backwards.
		right.backward(pwmModule, 0);
		left.backward(pwmY, 0);
	}
	else if (x > 0 && y < 0) {
		right.backward(pwmY, 0);
		left.backward(pwmModule, 0);
	}
}

/**
 * @brief Toggle the servo motor action
 *
 */
void MachineRoom::flip(void)
{
	servo.flip();
}

/**
 * @brief Change the friction and the friction step of the robot according to an incoming parameter.
 *
 * @param friction unsigned char but limited between 1-5
 */
void MachineRoom::changeFriction(uint8_t friction)
{
	this->friction     = MOTOR_PWM_RANGE;
	this->frictionStep = MOTOR_PWM_RANGE / friction;
}

/**
 * @brief Change the speed ratio of the robot according to an incoming parameter.
 *
 * @param speed as an unsigned char
 */
void MachineRoom::changeSpeed(uint8_t speed)
{
	this->speedRatio = (float)speed / 100.0;
}

/**
 * @brief Change the state of the feedback led
 *
 * @param level as a boolean
 */
void MachineRoom::changeFeedback(bool level)
{
	digitalWrite(FEEDBACK_LED, level);
}
