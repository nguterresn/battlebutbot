#include <Arduino.h>
#include "Driver.h"

#define MOTOR_VALUE_MASK 0b11100100 // Limited to 100 and -100;

class Motor {
  public:
    Motor(uint8_t xIN1, uint8_t xIN2);
    Stream *serial;
    void installLogger(Stream *serial);
    void update(int x, int y);
  private:
    Driver driver;
};
