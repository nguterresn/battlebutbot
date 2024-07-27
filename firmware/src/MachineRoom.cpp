#include "MachineRoom.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

// Configuration cache
settings_t robot_settings;

// Models (class based)
static Motor left(MOTOR_LEFT1, MOTOR_LEFT2, MOTOR_LEFT1_CHANNEL, MOTOR_LEFT2_CHANNEL);
static Motor right(MOTOR_RIGHT1, MOTOR_RIGHT2, MOTOR_RIGHT1_CHANNEL, MOTOR_RIGHT2_CHANNEL);

// Private Functions
static void machine_room_forward(uint8_t pwm);
static void machine_room_backward(uint8_t pwm);
static void machine_room_brake(void);

void machine_room_init(void)
{
  pinMode(MOTOR_FAULT, INPUT_PULLUP);
}

/**
 * @brief Resets machine room by stopping the motors or returning them to initial position.
 *
 */
void machine_room_reset(void)
{
  machine_room_brake();
}

/**
 * @brief Whenever the car needs to just go forward
 *
 * @param pwm as an unsigned char from 0 to MOTOR_PWM_RANGE
 */
static inline void machine_room_forward(uint8_t pwm)
{
  right.forward(pwm);
  left.forward(pwm);
}

/**
 * @brief Whenever the car needs to just go backward
 *
 * @param pwm as an unsigned char from 0 to MOTOR_PWM_RANGE
 */
static inline void machine_room_backward(uint8_t pwm)
{
  right.backward(pwm);
  left.backward(pwm);
}

/**
 * @brief Whenever the car needs to break
 *
 */
static void machine_room_brake(void)
{
  right.brake();
  left.brake();
}

/**
 * @brief Update motors according to web's joystick incoming data.
 *
 * @param x incoming x axis integer from web's joystick.
 * @param y incoming y axis integer from web's joystick.
 */
void machine_room_update(int speed, int y, int x)
{
  // The Y axis informs us the power we should provide to the motors, whereas
  // the X axis informs us about the direction the car should go.

  if (speed == 0) {
    machine_room_brake();
    return;
  }

  double radian         = atan2(abs(y), abs(x));
  uint16_t sin_mapped_y = speed * sin(radian);

  uint8_t _PWMspeed     = map(abs(speed), 0, 100, 0, MOTOR_PWM_RANGE);
  uint8_t _PWMmodule_y  = map(sin_mapped_y, 0, 100, 0, MOTOR_PWM_RANGE);

  // Serial.printf("Speed in pwm: %d\n", _PWMspeed);

  if (x == 0) {
    speed > 0 ? machine_room_forward(_PWMspeed) : machine_room_backward(_PWMspeed);
  }
  else if (x > 0 && speed > 0) {
    // 1st quadrant - forward and right.
    right.forward(_PWMmodule_y);
    left.forward(_PWMspeed);
  }
  else if (x < 0 && speed > 0) {
    // 2nd quadrant - forward and left.
    right.forward(_PWMspeed);
    left.forward(_PWMmodule_y);
  }
  else if (x < 0 && speed < 0) {
    // 3rd quandrant
    right.backward(_PWMspeed);
    left.backward(_PWMmodule_y);
  }
  else if (x > 0 && speed < 0) {
    // 4th quandrant
    right.backward(_PWMmodule_y);
    left.backward(_PWMspeed);
  }
}
