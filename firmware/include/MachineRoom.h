#include <Arduino.h>
#include "Motor.h"

class MachineRoom {
public:
	MachineRoom(uint8_t leftMotorIN1, uint8_t leftMotorIN2, uint8_t rightMotorIN1, uint8_t rightMotorIN2);
	void installLogger(Stream* serial);
	void forward(uint8_t pwm);
	void backwards(uint8_t pwm);
	void brake();
	void connect();
	void update(int x, int y);
private:
	Stream* serial;
	Motor left, right;
};
