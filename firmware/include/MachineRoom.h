#include "models/Motor.h"
#include "models/ServoMotor.h"
#include "constants/PinList.h"

#define SPEED_DEFAULT         MOTOR_PWM_RANGE // Descending speed (255 -> 1)
#define PWM_DEFAULT_FREQUENCY 500

class MachineRoom {
public:
	MachineRoom(Stream* serial = nullptr);
	void reset(void);
	void forward(uint8_t pwm);
	void backward(uint8_t pwm);
	void brake(void);
	void update(int x, int y);
	void flip(void);
	void changeSpeed(uint8_t speed);
	void changeFeedback(bool level);
private:
	Stream* serial;
	Motor left, right;
	ServoMotor servo;

	float speedRatio;
};
