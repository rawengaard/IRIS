#ifndef Circle_h
#define Circle_h

#include <Arduino.h>

class Circle {
  public:
    Circle(uint32_t my_delay, int startLed, int endLed, uint32_t color);
    boolean getStatus();
    void activate();
    void checkTimer();
    int getStart();
    int getEnd();
    uint32_t getColor();
  private:
    boolean _status;
    uint32_t _timerStart;
    uint32_t _delay;
    int _startLed;
    int _endLed;
    uint32_t _color;
};
#endif
