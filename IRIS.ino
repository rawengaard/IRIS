/*
    IRIS - Spire - IN1060 - v21

    This is the main program for the IRIS sound mat. The mat has 11 circles the user is
    supposed to step on. When stepped on, the sensor will activate the circle, display leds,
    and send a signal to a computer to play sounds. That way, this mat will serve as an instrument.
*/

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel mainStrip (408, 45, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel cabinetStrip (47, 44, NEO_GRB + NEO_KHZ800);

#include <CapacitiveSensor.h>
CapacitiveSensor sensors[] = {
  {22, 23}, {24, 25}, {26, 27}, {28, 29},
  {30, 31}, {32, 33}, {34, 35}, {36, 37},
  {38, 39}, {40, 41}, {42, 43}
};

#include "Circle.h"
// store the colors (HEX) in variables
const uint32_t red    = Adafruit_NeoPixel::Color(0xFF, 0x00, 0x00);
const uint32_t orange = Adafruit_NeoPixel::Color(0xFF, 0x78, 0x00);
const uint32_t yellow = Adafruit_NeoPixel::Color(0xFF, 0xFF, 0x00);
const uint32_t green  = Adafruit_NeoPixel::Color(0x00, 0xFF, 0x00);
const uint32_t blue   = Adafruit_NeoPixel::Color(0x00, 0x00, 0x7F);
const uint32_t off    = Adafruit_NeoPixel::Color(0x00, 0x00, 0x00);

// store the circles in a list
// Circle(delay, startLed, endLed, color)
 Circle circles[] = {
  {2000, 0, 37, yellow}, {4000, 38, 74, red}, {8000, 75, 111, orange}, {3000, 112, 148, green},
  {3000, 149, 185, red}, {4200, 185, 222, orange}, {3000, 223, 259, red}, {2000, 260, 296, yellow},
  {4200, 297, 333, orange}, {3100, 334, 370, red}, {3500, 371, 407, yellow}
};

const byte circleCount = sizeof circles / sizeof circles[0];       // the number of circles
// sizeof(array) returns the number of bytes the array occupies.
// Since each element can take more than 1 byte of space, the result have to be divided by
// the size of one element (sizeof(array[0]). This gives you the number og elements in the array

// read a sensor, update the status of the Circle
void readSensor(byte i, CapacitiveSensor& sensor, Circle& circle) {
  const int threshold = 700;                             // when should the circle be activated?
  if (circle.getStatus()== false) {                      // if passive, test sensor
    long sensorValue = sensor.capacitiveSensor(30);      // read the sensor

    if (sensorValue > threshold) {
      circle.activate();                                 // activate the circle
      Serial.println(i+1);                               // print the number of the sensor/ button
    }
  }
}

// Turn on the leds on the cabinet
void cabinetLeds(uint32_t color, uint32_t wait) {
  for (int i = 0; i < cabinetStrip.numPixels(); i++) {
    cabinetStrip.setPixelColor(i, color);               // set the color
    cabinetStrip.show();                                // show/ update the pixel
    delay(wait);                                        // pause for a moment between each pixel
  }
}

void displayLeds(Circle& circle) {
  for (int i = circle.getStart(); i < circle.getEnd(); i++)
    if (circle.getStatus())  mainStrip.setPixelColor(i, circle.getColor());     // set the leds to the correct color
    else mainStrip.setPixelColor(i, off);                                       // turn the leds off
  mainStrip.show();                                                             // update led
}

void setup() {
  Serial.begin(115200);        // start the Serial communication
  mainStrip.begin();           // Initialize NeoPixel strip object
  mainStrip.setBrightness(50); // Set brightness to about 1/5 (max = 255)
  mainStrip.show();            // Turn off all pixels

  cabinetStrip.begin();
  cabinetStrip.show();
  cabinetStrip.setBrightness(50);
  cabinetLeds(blue, 50);            // turn on the Leds on the cabinet
  Serial.println("Setup complete.");
}

void loop() {
  for (byte i = 0; i < circleCount; i++) {
    circles[i].checkTimer();
    readSensor(i,  sensors[i],  circles[i]);
    displayLeds(circles[i]);
  }
  //Serial.println("0");            // this will stop Processing from repeating the last sound again and again
}
