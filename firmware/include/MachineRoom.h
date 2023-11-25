#ifndef MACHINE_ROOM_H_
#define MACHINE_ROOM_H_

#include <stdint.h>
#include "constants/PinList.h"
#include "constants/ConfigurationFields.h"
#include "models/Motor.h"

#define SPEED_DEFAULT       MOTOR_PWM_RANGE   // Descending speed (255 -> 1)
#define DEFAULT_TASK_STACK  configMINIMAL_STACK_SIZE* 10
#define DRIFT_DEFAULT       50

struct settings {
	uint8_t configuration;
	uint8_t speed;              //!< From 0 - 255
	uint8_t drift;              //!< From 0 - 100
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
