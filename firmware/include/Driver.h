#include <Arduino.h>

class Driver {
  public:
    Driver();
    Driver(uint8_t xIN1, uint8_t xIN2);
    void update(bool forward, uint8_t pwm);
  private:
    uint8_t xIN1, xIN2;
};
