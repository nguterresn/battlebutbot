#include <Arduino.h>
#include "controls.h"

void controls_begin()
{
	pinMode(POT_X, INPUT);
	pinMode(POT_Y, INPUT);
}

int read_x()
{
	return analogRead(POT_X);
}

int read_y()
{
	return analogRead(POT_Y);
}
