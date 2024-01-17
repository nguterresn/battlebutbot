#ifndef MACHINE_ROOM_H_
#define MACHINE_ROOM_H_

#include <stdint.h>
#include "constants/PinList.h"
#include "constants/ConfigurationFields.h"
#include "constants/MotorSettings.h"
#include "models/Motor.h"

struct settings {
	uint8_t configuration;
	uint8_t speed;              //!< From 1 - 255, default 255
	uint8_t drift;              //!< From 50 - 150, default 100
};

struct axis {
	// !! Shared resource !!
	int     x;
	int     y;
	uint8_t target_pwm;
	uint8_t target_compensation_pwm;
	// Non-Shared resource (safe)
	uint8_t current_pwm;
	uint8_t current_compensation_pwm;
};

typedef struct settings settings_t;

void machine_room_init(void);
void machine_room_reset(void);
void machine_room_update(int x, int y);
void machine_room_flip(void);
void machine_room_change(settings_t* settings);

bool machine_room_is_feedback_led_enabled(uint8_t configuration);
bool machine_room_is_servo_enabled(uint8_t configuration);
bool machine_room_is_auto_mode_enabled(uint8_t configuration);

#endif /* MACHINE_ROOM_H_ */
