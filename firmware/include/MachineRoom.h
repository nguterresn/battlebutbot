#include "Motor.h"
#include "ServoMotor.h"

// Theorectically speaking with a CPU_FREQ of 80Mhz, each tick would be executed
// every 0.0125 ms. This leaves us with a non-blocking friction window
// of 0 to 0.0125 * 255 = 3.18ms.
#define FRICTION_DEFAULT 1               // Ascending friction (1 -> 5)
#define SPEED_DEFAULT    MOTOR_PWM_RANGE // Descending speed (255 -> 1)

class MachineRoom {
public:
	MachineRoom(uint8_t leftMotorIN1, uint8_t leftMotorIN2, uint8_t rightMotorIN1, uint8_t rightMotorIN2, uint8_t servoPin, Stream* serial = nullptr);
	void reset(void);
	void forward(uint8_t pwm);
	void backward(uint8_t pwm);
	void brake(void);
	void update(int x, int y);
	void flip(void);
	void changeFriction(uint8_t step);
	void changeSpeed(uint8_t speed);
private:
	Stream* serial;
	Motor left, right;
	ServoMotor servo;

	uint8_t frictionStep, friction;
	float speedRatio;
};
