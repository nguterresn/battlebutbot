#include <Arduino.h>

class Motor {
  public:
    Stream *serial;
    void installLogger(Stream *serial);
    void update(unsigned char x, unsigned char y);
};
