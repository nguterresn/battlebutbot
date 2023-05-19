#include "Motor.h"

#define FRICTION      2                                     // Ascending friction (1 - 255)
#define FRICTION_STEP MOTOR_PWM_RANGE / FRICTION            // Ascending friction

class MachineRoom {
public:
	MachineRoom();
	MachineRoom(uint8_t leftMotorIN1, uint8_t leftMotorIN2, uint8_t rightMotorIN1, uint8_t rightMotorIN2, uint8_t step = FRICTION_STEP);
	void forward(uint8_t pwm);
	void backward(uint8_t pwm);
	void brake();
	void update(int x, int y);
	// void changeLeftMotorFriction(uint8_t step);
	// void changeRightMotorFriction(uint8_t step);
private:
	Motor left, right;
	uint8_t friction = MOTOR_PWM_RANGE, wasForward = false, step;
};
