#include <Arduino.h>
#include "controls.h"
#include "main.h"

bool select_has_pressed = false;
bool select_last_state  = false;
bool right_has_pressed  = false;
bool right_last_state   = false;
bool left_last_state    = false;
bool left_has_pressed   = false;

void controls_begin()
{
	pinMode(SELECT_BUTTON, INPUT_PULLUP);
	pinMode(JOYSTICK_LEFT_BUTTON, INPUT_PULLUP);
	pinMode(JOYSTICK_RIGHT_BUTTON, INPUT_PULLUP);

	pinMode(JOYSTICK_RIGHT_Y, INPUT);
	pinMode(JOYSTICK_RIGHT_X, INPUT);
	pinMode(JOYSTICK_LEFT_X, INPUT);
	pinMode(JOYSTICK_LEFT_Y, INPUT);
}

void controls_loop(void* v)
{
	(void)v;
	for (;;) {
		bool select_current_state = digitalRead(SELECT_BUTTON);
		if (select_last_state != select_current_state) {
			if (select_current_state == 0) {
				select_has_pressed = true;
			}
		}
		select_last_state = select_current_state;

		bool left_current_state = digitalRead(JOYSTICK_LEFT_BUTTON);
		if (left_last_state != left_current_state) {
			if (left_current_state == 0) {
				left_has_pressed = true;
			}
		}
		left_last_state = left_current_state;

		bool right_current_state = digitalRead(JOYSTICK_RIGHT_BUTTON);
		if (right_last_state != right_current_state) {
			if (right_current_state == 0) {
				right_has_pressed = true;
			}
		}
		right_last_state = right_current_state;
		vTaskDelay(10);
	}
}

bool select_pressed()
{
	if (select_has_pressed) {
		select_has_pressed = false;
		return true;
	}
	return false;
}

bool left_pressed()
{
	if (left_has_pressed) {
		left_has_pressed = false;
		return true;
	}
	return false;
}

bool right_pressed()
{
	if (right_has_pressed) {
		right_has_pressed = false;
		return true;
	}
	return false;
}

int read_left_x()
{
	return analogRead(JOYSTICK_LEFT_X);
}

int read_left_y()
{
	return analogRead(JOYSTICK_LEFT_Y);
}

int read_right_x()
{
	return analogRead(JOYSTICK_RIGHT_X);
}

int read_right_y()
{
	return analogRead(JOYSTICK_RIGHT_Y);
}
