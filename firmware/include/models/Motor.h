#include <Arduino.h>

#define JOYSTICK_MASK            0x64 // Limited to 100;
#define MOTOR_JOYSTICK_THRESHOLD 20

#define MOTOR_PWM_RANGE          255

// Choose the type of motor decay
// #define LOW_POWER                // fast decay
#define HIGH_PERFORMANCE         // slow decay

class Motor {
public:
	Motor(uint8_t xIN1 = 0, uint8_t xIN2 = 0);
	void update(uint8_t xIN1pwm, uint8_t xIN2pwm);
	void brake(void);
	void forward(uint8_t pwm);
	void backward(uint8_t pwm);
private:
	uint8_t xIN1, xIN2;
};