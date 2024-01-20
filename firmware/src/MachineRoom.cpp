#include "MachineRoom.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "models/ServoMotor.h"
#include "models/ProximitySensor.h"

#define ACCELERATION 2

// Configuration cache
settings_t robot_settings;
static struct axis axis;
static uint8_t mode;

// FreeRTOS mutex
static SemaphoreHandle_t mutex;

// Models (class based)
static ProximitySensor irSensorLeft(PROXIMITY_SENSOR_LEFT), irSensorRight(PROXIMITY_SENSOR_RIGHT);
static Motor left(MOTOR_LEFT1, MOTOR_LEFT2, MOTOR_LEFT1_CHANNEL, MOTOR_LEFT2_CHANNEL);
static Motor right(MOTOR_RIGHT1, MOTOR_RIGHT2, MOTOR_RIGHT1_CHANNEL, MOTOR_RIGHT2_CHANNEL);
static ServoMotor servo(SERVO_FRONT);

// Private Functions
static void machine_room_forward(uint8_t pwm);
static void machine_room_backward(uint8_t pwm);
static void machine_room_brake(void);
static void machine_room_loop(void* v);

void machine_room_init(void)
{
	pinMode(FEEDBACK_LED, OUTPUT);

	machine_room_brake();
	BaseType_t result = xTaskCreate(machine_room_loop,
	                                "machine_room_loop",
	                                4096,
	                                NULL,
	                                tskIDLE_PRIORITY,
	                                NULL);

	mutex = xSemaphoreCreateMutex();
	if (mutex == NULL || result != pdPASS) {
		configASSERT(0);
	}
}

static void machine_room_loop(void* v)
{
	(void)v;
	uint8_t target_pwm = 0, target_compensation_pwm = 0;
	int x = 0, y = 0;

	for (;;) {
		if (xSemaphoreTake(mutex, 0)) {
			// !! Critical section !!
			x                       = axis.x;
			y                       = axis.y;
			target_pwm              = axis.target_pwm;
			target_compensation_pwm = axis.target_compensation_pwm;
			// !! Critical section !!
			xSemaphoreGive(mutex);

			// Speed
			if (axis.current_pwm < target_pwm) {
				axis.current_pwm = min(axis.current_pwm + ACCELERATION, target_pwm);
			}
			else if (axis.current_pwm > target_pwm) {
				axis.current_pwm = max(axis.current_pwm - ACCELERATION, target_pwm);
			}
			// Compensation
			if (axis.current_compensation_pwm < target_compensation_pwm) {
				axis.current_compensation_pwm = min(axis.current_compensation_pwm + ACCELERATION,
				                                    target_compensation_pwm);
			}
			else if (axis.current_compensation_pwm > target_compensation_pwm) {
				axis.current_compensation_pwm = max(axis.current_compensation_pwm - ACCELERATION,
				                                    target_compensation_pwm);
			}

			if ((x == 0 && y == 0) || abs(y) < MOTOR_JOYSTICK_DEAD_ZONE) {
				machine_room_brake();
			}
			else if (abs(x) < MOTOR_JOYSTICK_DEAD_ZONE) {
				y > 0 ?
				machine_room_forward(axis.current_pwm) :
				machine_room_backward(axis.current_pwm);
			}
			else if (x > 0 && y > 0) {
				// 1st quadrant - forward and right.
				right.forward(axis.current_compensation_pwm);
				left.forward(axis.current_pwm);
			}
			else if (x < 0 && y > 0) {
				// 2nd quadrant - forward and left.
				right.forward(axis.current_pwm);
				left.forward(axis.current_compensation_pwm);
			}
			// 3rd & 4th quandrant - backwards.
			else if ((x < 0 && y < 0) || (x > 0 && y < 0)) {
				//!< There is a bug here....
				machine_room_backward(axis.current_pwm);
			}
			// 3rd
			// right.backward(axis.current_pwm);
			// left.backward(axis.current_compensation_pwm);
			// 4th
			// right.backward(axis.current_compensation_pwm);
			// left.backward(axis.current_pwm);
		}
		vTaskDelay(5 / portTICK_RATE_MS);
	}
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
 * @brief Measure and update motors drift
 *
 * @param drift between 50 and 150
 */
static void machine_room_update_drift(uint8_t drift)
{
	uint8_t rightDrift = MOTOR_DRIFT_DEFAULT;
	uint8_t leftDrift  = MOTOR_DRIFT_DEFAULT;

	if (drift > MOTOR_DRIFT_DEFAULT) {
		// The car should lean towards the right. Increase left motor drift.
		leftDrift = max(MOTOR_DRIFT_MAX_INPUT - drift + MOTOR_DRIFT_MIN_INPUT,
		                MOTOR_DRIFT_MIN_INPUT);
	}
	else if (drift < MOTOR_DRIFT_DEFAULT) {
		// The car should lean towards the left. Increase right motor drift.
		rightDrift = max(drift, MOTOR_DRIFT_MIN_INPUT);
	}

	right.update(rightDrift);
	left.update(leftDrift);
}

/**
 * @brief Whenever the car needs to just go forward
 *
 * @param pwm as an unsigned char from 0 to MOTOR_PWM_RANGE
 */
static void machine_room_forward(uint8_t pwm)
{
	right.forward(pwm);
	left.forward(pwm);
}

/**
 * @brief Whenever the car needs to just go backward
 *
 * @param pwm as an unsigned char from 0 to MOTOR_PWM_RANGE
 */
static void machine_room_backward(uint8_t pwm)
{
	right.backward(pwm);
	left.backward(pwm);
}

/**
 * @brief Whenever the car needs to break
 *
 */
static void machine_room_brake(void)
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
	if (xSemaphoreTake(mutex, 10)) {
		if (x == axis.x && y == axis.y) {
			xSemaphoreGive(mutex);
			return;
		}

		axis.x = x; // Cache 'x'
		axis.y = y; // Cache 'y'

		// Whenever the joystick returns to zero, stop.
		if (x == 0 && y == 0) {
			axis.target_pwm              = 0;
			axis.target_compensation_pwm = 0;
		}
		else {
			// The Y axis informs us the power we should provide to the motors, whereas
			// the X axis informs us about the direction the car should go.
			double radian     = atan2(abs(y), abs(x));
			uint8_t module    = min(sqrt((double)pow(abs(y), 2) + pow(abs(x), 2)), (double)JOYSTICK_MASK);
			uint8_t pwmModule = module * ((float)robot_settings.speed / 100.00);
			uint8_t pwmY      = pwmModule * sin(radian);

			axis.target_pwm              = pwmModule;
			axis.target_compensation_pwm = pwmY;
		}

		xSemaphoreGive(mutex);
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
 * @param settings with the robot settings
 */
void machine_room_change(settings_t* settings)
{
	digitalWrite(FEEDBACK_LED,
	             machine_room_is_feedback_led_enabled(settings->configuration));
	servo.update(machine_room_is_servo_enabled(settings->configuration));
	machine_room_update_drift(settings->drift);
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
