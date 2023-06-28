#include "esp32-hal-ledc.h"
#include "esp32-hal-log.h"
#include <math.h>

// Include others if needed.
#define SERVO_SG90             // http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/stores/sg90_datasheet.pdf

#ifdef SERVO_SG90
#define MIN_ANGLE_IN_US        1000
#define _0_ANGLE_IN_US         1500
#define MAX_ANGLE_IN_US        2000
#endif

#define SERVO_CHANNEL          0
#define PWM_DEFAULT_FREQUENCY  500
#define PWM_DEFAULT_RESOLUTION 16

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

class ServoMotor {
public:
	ServoMotor(uint8_t pin);
	void update(bool enable);
	void reset(void);
	void write(uint32_t usec);
	void flip(void);
	bool isFlipped(void);

private:
	bool enabled, flipped;
	uint32_t min, max;
};
