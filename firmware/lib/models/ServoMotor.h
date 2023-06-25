// https://github.com/esp8266/Arduino/tree/master/libraries/Servo
#ifdef ESP32
#include <ESP32Servo.h>
#elif ESP8266
#include <Servo.h>
#endif

// Include others if needed.
#define SERVO_SG90         // http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/stores/sg90_datasheet.pdf

#ifdef SERVO_SG90
#define MIN_ANGLE_IN_US    1000
#define NEG_90_ANGLE_IN_US 1000
#define _0_ANGLE_IN_US     1500
#define POS_90_ANGLE_IN_US 2000
#define MAX_ANGLE_IN_US    2000
#endif

class ServoMotor {
public:
	ServoMotor(uint8_t pin);
	void update(bool enable);
	void reset(void);
	void flip(void);
	bool isFlipped(void);

private:
	Servo _servo;
	bool enabled, flipped;
};
