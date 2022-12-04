#include <Arduino.h>

#define MOTOR_FORWARD_MASK 0x64 // Limited to 100 and -100;
#define MOTOR_BACKWARDS_MASK 0xFFFFFF64 // Limited to 100 and -100;
#define MOTOR_THRESHOLD 15

class Motor {
  public:
    Motor();
    Motor(uint8_t xIN1, uint8_t xIN2);
    void update(uint8_t xIN1pwm, uint8_t xIN2pwm);
  private:
    uint8_t xIN1, xIN2;
};
