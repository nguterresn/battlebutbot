#include "Motor.h"

class MachineRoom {
public:
	MachineRoom();
	MachineRoom(uint8_t leftMotorIN1, uint8_t leftMotorIN2, uint8_t rightMotorIN1, uint8_t rightMotorIN2);
	void forward(uint8_t pwm);
	void backwards(uint8_t pwm);
	void brake();
	void update(int x, int y);
private:
	Motor left, right;
};
