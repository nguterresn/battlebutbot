#include <Arduino.h>

#define JOYSTICK_MASK            0x64 // Limited to 100;
#define MOTOR_JOYSTICK_THRESHOLD 20

#define MOTOR_PWM_RANGE          255

class Motor {
public:
	Motor();
	Motor(uint8_t xIN1, uint8_t xIN2);
	void update(uint8_t xIN1pwm, uint8_t xIN2pwm);
	void forward(uint8_t pwm);
	void reverse(uint8_t pwm);
private:
	uint8_t xIN1, xIN2;
};
