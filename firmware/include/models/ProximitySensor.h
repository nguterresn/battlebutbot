#include <Arduino.h>

#define PROXIMITY_ADC_THRESHOLD 1500 // up to 4096. (12 bits)

class ProximitySensor {
public:
	ProximitySensor(uint8_t pin);
	bool isClose(void);

private:
	int read(void);
	uint8_t pin;
};
