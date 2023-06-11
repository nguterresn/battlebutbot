#include "Motor.h"
#include "ServoMotor.h"

// Theorectically speaking with a CPU_FREQ of 80Mhz, each tick would be executed
// every 0.0125 ms. This leaves us with a non-blocking friction window
// of 0 to 0.0125 * 255 = 3.18ms.
#define FRICTION_DEFAULT 1               // Ascending friction (1 -> 5)
#define SPEED_DEFAULT    MOTOR_PWM_RANGE // Descending speed (255 -> 1)

#ifdef ESP8266
#define LEFT1            D1
#define LEFT2            D2
#define RIGHT1           D5
#define RIGHT2           D4

#define SERVO            D6
#define BATTERY_SENSOR   A0
#define FEEDBACK_LED     D7
#elif ESP32
// include it later.
#endif

class MachineRoom {
public:
	MachineRoom(Stream* serial = nullptr);
	void reset(void);
	void forward(uint8_t pwm);
	void backward(uint8_t pwm);
	void brake(void);
	void update(int x, int y);
	void flip(void);
	void changeFriction(uint8_t step);
	void changeSpeed(uint8_t speed);
	void changeFeedback(bool level);
private:
	Stream* serial;
	Motor left, right;
	ServoMotor servo;

	uint8_t frictionStep, friction;
	float speedRatio;
};
