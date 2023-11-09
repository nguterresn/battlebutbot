#ifndef MACHINE_ROOM_H_
#define MACHINE_ROOM_H_

#include "constants/PinList.h"
#include "constants/ConfigurationFields.h"
#include <stdint.h>
#include "models/Motor.h"

#define SPEED_DEFAULT      MOTOR_PWM_RANGE    // Descending speed (255 -> 1)
#define DEFAULT_TASK_STACK configMINIMAL_STACK_SIZE* 10

void machine_room_init(void);
void machine_room_reset(void);
void machine_room_update(int x, int y);
void machine_room_flip(void);
void machine_room_change(uint8_t configuration, uint8_t speed);

bool machine_room_is_feedback_led_enabled(uint8_t configuration);
bool machine_room_is_servo_enabled(uint8_t configuration);
bool machine_room_is_auto_mode_enabled(uint8_t configuration);

#endif /* MACHINE_ROOM_H_ */
