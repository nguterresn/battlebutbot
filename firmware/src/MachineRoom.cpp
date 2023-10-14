#include "MachineRoom.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Buzzer.h"
#include "models/ServoMotor.h"
#include "models/ProximitySensor.h"

static ProximitySensor irSensorLeft(PROXIMITY_SENSOR_LEFT), irSensorRight(PROXIMITY_SENSOR_RIGHT);
static Motor left(MOTOR_LEFT1, MOTOR_LEFT2), right(MOTOR_RIGHT1, MOTOR_RIGHT2);
static ServoMotor servo(SERVO_FRONT);

static uint8_t mode;
static float speedRatio;

static TaskHandle_t proximitySensorTaskHandle, genericTaskHandle;

void machine_room_init(void)
{
	pinMode(FEEDBACK_LED, OUTPUT);
	buzzer_init();

	machine_room_change_speed(SPEED_DEFAULT);
}

/**
 * @brief Resets machine room by stopping the motors or returning them to initial position.
 *
 */
void machine_room_reset(void)
{
	machine_room_brake();
	servo.reset();
}

/**
 * @brief Whenever the car needs to just go forward
 *
 * @param pwm as an unsigned char from 0 to MOTOR_PWM_RANGE
 */
void machine_room_forward(uint8_t pwm)
{
	right.forward(pwm);
	left.forward(pwm);
}

/**
 * @brief Whenever the car needs to just go backward
 *
 * @param pwm as an unsigned char from 0 to MOTOR_PWM_RANGE
 */
void machine_room_backward_all(uint8_t pwm)
{
	right.backward(pwm);
	left.backward(pwm);
}

/**
 * @brief Whenever the car needs to just go backward
 *
 * @param pwm as an unsigned char from 0 to MOTOR_PWM_RANGE
 */
void machine_room_backward(uint8_t pwmLeft, uint8_t pwmRight)
{
	right.backward(pwmRight);
	left.backward(pwmLeft);
}

/**
 * @brief Whenever the car needs to break
 *
 */
void machine_room_brake(void)
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
void machine_room_update(int x, int y)
{
	// Whenever the joystick returns to zero, stop.
	if (x == 0 && y == 0) {
		machine_room_brake();
		return;
	}

	// Prevent any manual input if the robot is in auto mode.
	if (mode == AUTO) {
		mode = MANUAL;
		machine_room_free_tasks();
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
		y > 0 ? machine_room_forward(pwmY) : machine_room_backward_all(pwmY);
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
void machine_room_flip(void)
{
	servo.flip();
}

/**
 * @brief Change the configuration fields according to its bit value
 *
 * @param configuration as a bit field configuration
 */
void machine_room_change(uint8_t configuration, uint8_t speed)
{
	digitalWrite(FEEDBACK_LED, machine_room_is_feedback_led_enabled(configuration));
	servo.update(machine_room_is_servo_enabled(configuration));
	machine_room_change_speed(speed);

	// Anytime the configuration changes, emit a sound.
	xTaskCreate(buzzer_beep,
	            "buzzer_beep",
	            configMINIMAL_STACK_SIZE, NULL, 0, NULL);

	if (machine_room_is_auto_mode_enabled(configuration)) {
		mode = AUTO;
		machine_room_forward(100);

		if (!proximitySensorTaskHandle) {
			xTaskCreate(machine_room_proximity_sensor_decision,
			            "machine_room_proximity_sensor_decision",
			            configMINIMAL_STACK_SIZE,
			            NULL,
			            0,
			            &proximitySensorTaskHandle);
		}
	}
	else {
		mode = MANUAL;
		// TODO: Save on EEPROM as well.
		machine_room_free_tasks();
		machine_room_brake();
	}
}

/**
 * @brief Change the speed ratio of the robot according to an incoming parameter.
 *
 * @param speed as an unsigned char
 */
void machine_room_change_speed(uint8_t speed)
{
	speedRatio = (float)speed / 100.0;
}

/**
 * @brief Checks if the feedback led is enable
 *
 * @return bool
 */
bool machine_room_is_feedback_led_enabled(uint8_t configuration)
{
	return configuration & ENABLE_FEEDBACK_LED ? true : false;
}

/**
 * @brief Checks if the servo is enable
 *
 * @return bool
 */
bool machine_room_is_servo_enabled(uint8_t configuration)
{
	return configuration & ENABLE_SERVO ? true : false;
}

/**
 * @brief Checks if the auto mode is enabled
 *
 * @return bool
 */
bool machine_room_is_auto_mode_enabled(uint8_t configuration)
{
	return configuration & ENABLE_AUTO_MODE ? true : false;
}

void machine_room_proximity_sensor_decision(void* v)
{
	(void)v;
	for (;;) {
		bool state = irSensorLeft.isClose() || irSensorRight.isClose();
		if (state && !genericTaskHandle) {
			xTaskCreate(machine_room_move_backwards_and_resume,
			            "machine_room_move_backwards_and_resume",
			            configMINIMAL_STACK_SIZE,
			            NULL,
			            0,
			            &genericTaskHandle);
		}
		vTaskDelay(50 / portTICK_RATE_MS);
	}
}

void machine_room_move_backwards_and_resume(void* v)
{
	bool left  = irSensorLeft.isClose();
	bool right = irSensorRight.isClose();

	if (left && right) {
		// Random one but later we can compare according to the ADC read values.
		machine_room_backward(200, 75);
	}
	else if (left) {
		machine_room_backward(200, 75);
	}
	else if (right) {
		machine_room_backward(75, 200);
	}

	vTaskDelay(1500 / portTICK_RATE_MS);
	machine_room_forward(100);

	genericTaskHandle = NULL;
}

void machine_room_free_tasks(void)
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
