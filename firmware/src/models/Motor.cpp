#include "models/Motor.h"
#include "constants/MotorSettings.h"

// To improve brushed motors:
// https://learn.adafruit.com/improve-brushed-dc-motor-performance?view=all
/**
 * @brief Construct a new Motor:: Motor object
 *
 * @param xIN1 as a pin
 * @param xIN2 as a pin
 */
Motor::Motor(uint8_t xIN1_pin, uint8_t xIN2_pin, uint8_t xIN1_channel, uint8_t xIN2_channel) :
  xIN1_channel(xIN1_channel), xIN2_channel(xIN2_channel)
{
  pinMode(xIN1_pin, OUTPUT);
  pinMode(xIN2_pin, OUTPUT);

  configASSERT(ledcSetup(xIN1_channel, MOTOR_PWM_FREQUENCY, MOTOR_PWM_RESOLUTION));
  configASSERT(ledcSetup(xIN2_channel, MOTOR_PWM_FREQUENCY, MOTOR_PWM_RESOLUTION));

  ledcAttachPin(xIN1_pin, xIN1_channel);
  ledcAttachPin(xIN2_pin, xIN2_channel);

  this->brake();
}

/**
 * @brief Update motor pwm pins (slow decay)
 *
 * @param xIN1pwm
 * @param xIN2pwm
 */
void Motor::move(uint8_t xIN1pwm, uint8_t xIN2pwm)
{
  ledcWrite(xIN1_channel, xIN1pwm);
  ledcWrite(xIN2_channel, xIN2pwm);
}

void Motor::brake(void)
{
#if defined(HIGH_PERFORMANCE)
  this->move(MOTOR_PWM_RANGE, MOTOR_PWM_RANGE);
#elif defined(LOW_POWER)
  this->move(0, 0);
#endif
}

/**
 * @brief Motor goes forward based on how big is the pwm argument (slow decay).
 *
 * @param pwm as a 8bit value, 255 is max speed
 */
void Motor::forward(uint8_t pwm)
{
#if defined(HIGH_PERFORMANCE)
  this->move(MOTOR_PWM_RANGE, MOTOR_PWM_RANGE - pwm);
#elif defined(LOW_POWER)
  this->move(pwm, 0);
#endif
}

/**
 * @brief Motor goes backwards based on how big is the pwm argument (slow decay).
 *
 * @param pwm as a 8bit value, 255 is max speed
 */
void Motor::backward(uint8_t pwm)
{
#if defined(HIGH_PERFORMANCE)
  this->move(MOTOR_PWM_RANGE - pwm, MOTOR_PWM_RANGE);
#elif defined(LOW_POWER)
  this->move(0, pwm);
#endif
}
