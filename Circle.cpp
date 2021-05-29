// CLass file for Circle
#include "Circle.h"

// constructor
Circle::Circle(uint32_t my_delay, int startLed, int endLed, uint32_t color) :
  _delay(my_delay), _startLed(startLed), _endLed(endLed), _color(color) {
  _timerStart = 0;
  _status = false;
}

void Circle::activate() {
  _status = true;
  _timerStart = millis();
}

void Circle::checkTimer() {
  _status = (millis() - _timerStart <= _delay);
}

boolean Circle::getStatus() {
  return _status;
}

int Circle::getStart() {
  return _startLed;
}

int Circle::getEnd() {
  return _endLed;
}

uint32_t Circle::getColor() {
  return _color;
}
