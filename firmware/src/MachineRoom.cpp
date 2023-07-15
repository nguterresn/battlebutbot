#include "MachineRoom.h"

TaskHandle_t proximitySensorTaskHandle = NULL;
TaskHandle_t genericTaskHandle         = NULL;

/**
 * @brief Construct a new Machine Room:: Machine Room object
 *
 */
MachineRoom::MachineRoom() :
	irSensorLeft(PROXIMITY_SENSOR_LEFT),
	irSensorRight(PROXIMITY_SENSOR_RIGHT),
	left(LEFT1, LEFT2),
	right(RIGHT1, RIGHT2),
	servo(SERVO),
	buzzer(BUZZER)
{
	pinMode(FEEDBACK_LED, OUTPUT);

	changeSpeed(SPEED_DEFAULT);
}

/**
 * @brief Resets machine room by stopping the motors or returning them to initial position.
 *
 */
void MachineRoom::reset(void)
{
	brake();
	servo.reset();
}

/**
 * @brief Whenever the car needs to just go forward
 *
 * @param pwm as an unsigned char from 0 to MOTOR_PWM_RANGE
 */
void MachineRoom::forward(uint8_t pwm)
{
	right.forward(pwm);
	left.forward(pwm);
}

/**
 * @brief Whenever the car needs to just go backward
 *
 * @param pwm as an unsigned char from 0 to MOTOR_PWM_RANGE
 */
void MachineRoom::backward(uint8_t pwm)
{
	right.backward(pwm);
	left.backward(pwm);
}

/**
 * @brief Whenever the car needs to just go backward
 *
 * @param pwm as an unsigned char from 0 to MOTOR_PWM_RANGE
 */
void MachineRoom::backward(uint8_t pwmLeft, uint8_t pwmRight)
{
	right.backward(pwmRight);
	left.backward(pwmLeft);
}

/**
 * @brief Whenever the car needs to break
 *
 */
void MachineRoom::brake(void)
{
	right.brake();
	left.brake();
}

/**
 * @brief Update motors according to web's joystick incoming data.
 *
 * @param x incoming x axis integer from web's joystick.
 * @param y incoming y axis integer from web's joystick.
 */
void MachineRoom::update(int x, int y)
{
	// Prevent any manual input if the robot is in auto mode.
	if (mode == AUTO && (x != 0 && y != 0)) {
		mode = MANUAL;
		resetFreeRTOS();
	}

	// Whenever the joystick returns to zero, stop.
	if (x == 0 && y == 0) {
		brake();
		return;
	}

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
		y > 0 ? forward(pwmY) : backward(pwmY);
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
		right.forward(pwmModule);
		left.forward(pwmY);
	}
	else if (x < 0 && y < 0) {
		// 3rd & 4th quandrant - backwards.
		right.backward(pwmModule);
		left.backward(pwmY);
	}
	else if (x > 0 && y < 0) {
		right.backward(pwmY);
		left.backward(pwmModule);
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
 * @brief Change the configuration fields according to its bit value
 *
 * @param configuration as a bit field configuration
 */
void MachineRoom::change(uint8_t configuration, uint8_t speed)
{
	digitalWrite(FEEDBACK_LED, isFeedbackLedEnabled(configuration));
	servo.update(isServoEnabled(configuration));
	changeSpeed(speed);

	// Anytime the configuration changes, emit a sound.
	xTaskCreate(Buzzer::beep, "Beep", 4096, NULL, 10, NULL);

	if (isAutoModeEnabled(configuration)) {
		mode = AUTO;
		forward(100);

		if (!proximitySensorTaskHandle) {
			xTaskCreate(ProximitySensorDecision,
			            "ProximitySensorDecision",
			            4096,
			            this,
			            10,
			            &proximitySensorTaskHandle);
		}
	}
	else {
		mode = MANUAL;
		// TODO: Save on EEPROM as well.
		resetFreeRTOS();
		brake();
	}
}

/**
 * @brief Change the speed ratio of the robot according to an incoming parameter.
 *
 * @param speed as an unsigned char
 */
void MachineRoom::changeSpeed(uint8_t speed)
{
	speedRatio = (float)speed / 100.0;
}

/**
 * @brief Checks if the feedback led is enable
 *
 * @return bool
 */
bool MachineRoom::isFeedbackLedEnabled(uint8_t configuration)
{
	return configuration & ENABLE_FEEDBACK_LED ? true : false;
}

/**
 * @brief Checks if the servo is enable
 *
 * @return bool
 */
bool MachineRoom::isServoEnabled(uint8_t configuration)
{
	return configuration & ENABLE_SERVO ? true : false;
}

/**
 * @brief Checks if the auto mode is enabled
 *
 * @return bool
 */
bool MachineRoom::isAutoModeEnabled(uint8_t configuration)
{
	return configuration & ENABLE_AUTO_MODE ? true : false;
}

void MoveBackwardsAndResume(void* machineRoom)
{
	MachineRoom* p = (MachineRoom*)machineRoom;
	bool left      = p->irSensorLeft.isClose();
	bool right     = p->irSensorRight.isClose();

	if (left && right) {
		// Random one but later we can compare according to the ADC read values.
		p->backward(200, 75);
	}
	else if (left) {
		p->backward(200, 75);
	}
	else if (right) {
		p->backward(75, 200);
	}

	vTaskDelay(1500 / portTICK_RATE_MS);
	p->forward(100);

	genericTaskHandle = NULL;
	vTaskDelete(genericTaskHandle);
}

void ProximitySensorDecision(void* machineRoom)
{
	for (;;) {
		MachineRoom* p = (MachineRoom*)machineRoom;

		bool state     = p->irSensorLeft.isClose() || p->irSensorRight.isClose();
		if (state && !genericTaskHandle) {
			xTaskCreate(MoveBackwardsAndResume,
			            "MoveBackwardsAndResume",
			            2048,
			            p,
			            10,
			            &genericTaskHandle);
		}
		vTaskDelay(50 / portTICK_RATE_MS);
	}
}

void resetFreeRTOS()
{
	if (proximitySensorTaskHandle) {
		vTaskDelete(proximitySensorTaskHandle);
	}
	if (genericTaskHandle) {
		vTaskDelete(genericTaskHandle);
	}
	proximitySensorTaskHandle = NULL;
	genericTaskHandle         = NULL;
}
