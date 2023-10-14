#include "constants/PinList.h"
#include "constants/ConfigurationFields.h"
#include <stdint.h>
#include "models/Motor.h"

#define SPEED_DEFAULT         MOTOR_PWM_RANGE // Descending speed (255 -> 1)
#define PWM_DEFAULT_FREQUENCY 500

void machine_room_init(void);
void machine_room_reset(void);
void machine_room_forward(uint8_t pwm);
void machine_room_backward(uint8_t pwmLeft, uint8_t pwmRight);
void machine_room_backward_all(uint8_t pwm);
void machine_room_brake(void);
void machine_room_update(int x, int y);
void machine_room_flip(void);
void machine_room_change(uint8_t configuration, uint8_t speed);
void machine_room_change_speed(uint8_t speed);

bool machine_room_is_feedback_led_enabled(uint8_t configuration);
bool machine_room_is_servo_enabled(uint8_t configuration);
bool machine_room_is_auto_mode_enabled(uint8_t configuration);

// FreeRTOS Tasks
void machine_room_move_backwards_and_resume(void* v);
void machine_room_proximity_sensor_decision(void* v);
void machine_room_free_tasks(void);
