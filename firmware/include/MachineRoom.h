#include "Motor.h"
#include "ServoMotor.h"
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
	void brake(void);
	void update(int x, int y);
	void flip(void);
	void change(uint8_t configuration);
	void changeSpeed(uint8_t speed);
	bool isFeedbackLedEnabled(uint8_t configuration);
	bool isServoEnabled(uint8_t configuration);
private:
	Motor left, right;
	ServoMotor servo;

	float speedRatio;
};
