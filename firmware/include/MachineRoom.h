#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Motor.h"
#include "ServoMotor.h"
#include "ProximitySensor.h"
#include "Buzzer.h"
#include "constants/PinList.h"
#include "constants/ConfigurationFields.h"

#define SPEED_DEFAULT         MOTOR_PWM_RANGE // Descending speed (255 -> 1)
#define PWM_DEFAULT_FREQUENCY 500

class MachineRoom {
public:
	MachineRoom();
	void reset(void);
	void forward(uint8_t pwm);
	void backward(uint8_t pwm);
	void backward(uint8_t pwmLeft, uint8_t pwmRight);
	void brake(void);
	void update(int x, int y);
	void flip(void);
	void change(uint8_t configuration, uint8_t speed);
	void changeSpeed(uint8_t speed);

	TaskHandle_t proximitySensorTaskHandle, genericTaskHandle;

	static void ProximitySensorDecision(void* machineRoom);
	static void MoveBackwardsAndResume(void* machineRoom);
	static void resetFreeRTOS(MachineRoom* machineRoom);

	ProximitySensor irSensorLeft;
	ProximitySensor irSensorRight;
private:
	bool isFeedbackLedEnabled(uint8_t configuration);
	bool isServoEnabled(uint8_t configuration);
	bool isAutoModeEnabled(uint8_t configuration);

	Motor left, right;
	ServoMotor servo;
	Buzzer buzzer;

	uint8_t mode;
	float speedRatio;
};
