#include <Arduino.h>

#define MOTOR_FORWARD_MASK 0x64 // Limited to 100 and -100;
#define MOTOR_THRESHOLD 15

#define MOTOR_PWM_RANGE 100

class Motor {
  public:
    Motor();
    Motor(uint8_t xIN1, uint8_t xIN2);
    void update(uint8_t xIN1pwm, uint8_t xIN2pwm);
    void forward(uint8_t pwm);
    void reverse(uint8_t pwm);
  private:
    uint8_t xIN1, xIN2;
};
