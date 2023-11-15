#include "models/ProximitySensor.h"

ProximitySensor::ProximitySensor(uint8_t pin)
{
	this->pin = pin;
	// pinMode(this->pin, INPUT);
}

int ProximitySensor::read(void)
{
	#ifdef ENABLE_IR
	return analogRead(this->pin);
	#else
	return 0;
	#endif
}

bool ProximitySensor::isClose(void)
{
	#ifdef ENABLE_IR
	return this->read() > PROXIMITY_ADC_THRESHOLD;
	#else
	return 0;
	#endif
}
