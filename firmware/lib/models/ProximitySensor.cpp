#include "ProximitySensor.h"

ProximitySensor::ProximitySensor(uint8_t pin)
{
	this->pin = pin;
	pinMode(this->pin, INPUT);
}

int ProximitySensor::read(void)
{
	return analogRead(this->pin);
}

bool ProximitySensor::isClose(void)
{
	// ESP_LOGW("ISCLOSE", " %d", this->read());
	return this->read() > PROXIMITY_ADC_THRESHOLD;
}
