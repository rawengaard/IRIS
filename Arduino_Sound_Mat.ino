/*
    Sound Mat - Spire - IN1060 - v21

    This is the main program for the Sound Mat. The mat has 11 circles the user is
    supposed to step on. When stepped on, the sensor will activate the circle, display leds,
    and send a signal to a computer to play sounds. That way, this mat will serve as an instrument.
*/

#include <Adafruit_NeoPixel.h>      
#include <CapacitiveSensor.h>       

// constants holding the colors
const auto red       = Adafruit_NeoPixel::Color(255,   0,   0);
const auto orange    = Adafruit_NeoPixel::Color(255, 120,   0);
const auto yellow    = Adafruit_NeoPixel::Color(255, 255,   0);
const auto green     = Adafruit_NeoPixel::Color(0,   255,   0);
const auto blue      = Adafruit_NeoPixel::Color(0,     0, 127);
const auto off       = Adafruit_NeoPixel::Color(0,     0,   0);

// Define data pin for LED strips for the circles
#define LED_PIN    45
// Define the length of the strip
// The strip is cut in sections. The first circle has 38 LEDs, the rest of the circles has 37 LEDs.
#define LED_COUNT 408
// Create NeoPixel object
Adafruit_NeoPixel strip (LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


// Define data pin for LED strips for the cabinet
#define LED_PIN_2    44
// Define the length of the strip
#define LED_COUNT_2 47
// Create NeoPixel object
Adafruit_NeoPixel strip_2 (LED_COUNT_2, LED_PIN_2, NEO_GRB + NEO_KHZ800);


//There will be 11 circles, with their own capacitive sensor.
CapacitiveSensor sensor_1   =  CapacitiveSensor(22, 23);
CapacitiveSensor sensor_2   =  CapacitiveSensor(24, 25);
CapacitiveSensor sensor_3   =  CapacitiveSensor(26, 27);
CapacitiveSensor sensor_4   =  CapacitiveSensor(28, 29);
CapacitiveSensor sensor_5   =  CapacitiveSensor(30, 31);
CapacitiveSensor sensor_6   =  CapacitiveSensor(32, 33);
CapacitiveSensor sensor_7   =  CapacitiveSensor(34, 35);
CapacitiveSensor sensor_8   =  CapacitiveSensor(36, 37);
CapacitiveSensor sensor_9   =  CapacitiveSensor(38, 39);
CapacitiveSensor sensor_10  =  CapacitiveSensor(40, 41);
CapacitiveSensor sensor_11  =  CapacitiveSensor(42, 43);

// Are the circles active?
boolean circle_1_status  = false;
boolean circle_2_status  = false;
boolean circle_3_status  = false;
boolean circle_4_status  = false;
boolean circle_5_status  = false;
boolean circle_6_status  = false;
boolean circle_7_status  = false;
boolean circle_8_status  = false;
boolean circle_9_status  = false;
boolean circle_10_status = false;
boolean circle_11_status = false;

// Time stamp for when the circle was set to active
unsigned long circle_1_start;
unsigned long circle_2_start;
unsigned long circle_3_start;
unsigned long circle_4_start;
unsigned long circle_5_start;
unsigned long circle_6_start;
unsigned long circle_7_start;
unsigned long circle_8_start;
unsigned long circle_9_start;
unsigned long circle_10_start;
unsigned long circle_11_start;

// Each circle has a delay that matches the corresponding sound clip
int circle_1_delay  = 2000;
int circle_2_delay  = 3000;
int circle_3_delay  = 8000;
int circle_4_delay  = 3100;
int circle_5_delay  = 4200;
int circle_6_delay  = 4000;
int circle_7_delay  = 3000;
int circle_8_delay  = 2000;
int circle_9_delay  = 8000;
int circle_10_delay = 3500;
int circle_11_delay = 3000;

// Turn on the leds on the cabinet
void cabinet_leds(uint32_t color, int wait) {
  for(int i=0; i<strip_2.numPixels(); i++) {      // all the leds
    strip_2.setPixelColor(i, color);              // set color to blue
    strip_2.show();                               // update led
    delay(wait);                                  // pause for a moment between each pixel
  }
}

// display the correct leds
void display_leds(){
    for (int i = 0; i<38; i++){                      // circle_1, 0-37, yellow
        if (circle_1_status == true){                // if the circle is active
            strip.setPixelColor(i, yellow);          // make the leds yellow
        } else {                                     // else
            strip.setPixelColor(i, off);             // turn the leds off
        }
    }
    for (int i = 38; i<75; i++){                     // circle_2, 38-74, red
        if (circle_2_status == true){
            strip.setPixelColor(i, red);
        } else {
            strip.setPixelColor(i, off);
        }
    }
    for (int i = 75; i<112; i++){                    // circle_3,74-111, orange
        if (circle_3_status == true){
            strip.setPixelColor(i, orange);
        } else {
            strip.setPixelColor(i, off);
        }
    }
    for (int i = 112; i<149; i++){                    // circle_4, 112-148, green
        if (circle_4_status == true){
            strip.setPixelColor(i, green);
        } else {
            strip.setPixelColor(i, off);
        }
    }
    for (int i = 149; i<186; i++){                    // circle_5, 149-185, red
        if (circle_5_status == true){
            strip.setPixelColor(i, red);
        } else {
            strip.setPixelColor(i, off);
        }
    }
    for (int i = 186; i<223; i++){                    // circle_6, 186-222, orange
        if (circle_6_status == true){
            strip.setPixelColor(i, orange);
        } else {
            strip.setPixelColor(i, off);
        }
    }
    for (int i = 223; i<260; i++){                    // circle_7, 223-259, red
        if (circle_7_status == true){
            strip.setPixelColor(i, red);
        } else {
            strip.setPixelColor(i, off);
        }
    }
    for (int i = 260; i<297; i++){                    // circle_8, 260-296, yellow
        if (circle_8_status == true){
            strip.setPixelColor(i, yellow);
        } else {
            strip.setPixelColor(i, off);
        }
    }
    for (int i = 297; i<334; i++){                    // circle_9, 297-333, orange
        if (circle_9_status == true){
            strip.setPixelColor(i, orange);
        } else {
            strip.setPixelColor(i, off);
        }
    }
    for (int i = 334; i<371; i++){                    // circle_10, 334-370, red
        if (circle_10_status == true){
            strip.setPixelColor(i, red);
        } else {
            strip.setPixelColor(i, off);
        }
    }
    for (int i = 371; i<408; i++){                    // circle_11, 371-407, yellow
        if (circle_11_status == true){
            strip.setPixelColor(i, yellow);
        } else {
            strip.setPixelColor(i, off);
        }
    }
    strip.show();                                     // show the updated LEDs
}

    unsigned long now = millis();

// ----------- S E T U P ------------------
void setup(){
    Serial.begin(9600);     // Initialize Serialconection
    strip.begin();           // Initialize NeoPixel strip object
    strip.show();            // Turn off all pixels ASAP
    strip.setBrightness(50); // Set brightness to about 1/5 (max = 255)

    strip_2.begin();
    strip_2.show();
    strip_2.setBrightness(50);

    // turn on the LEDs on the cabinet
    cabinet_leds(strip_2.Color(  0,   0, 255), 50);    // Blue
    delay(500);

    Serial.println("Setup complete.");

}

// ----------- L O O P --------------------
void loop(){
    // check the timers to see if some lights should be turned off
    now = millis();
    if (now > (circle_1_start + circle_1_delay)){
        circle_1_status = false;
    }

    now = millis();
    if (now > (circle_2_start + circle_2_delay)){
        circle_2_status = false;
    }

    now = millis();
    if (now > (circle_3_start + circle_3_delay)){
        circle_3_status = false;
    }

    now = millis();
    if (now > (circle_4_start + circle_4_delay)){
        circle_4_status = false;
    }

    now = millis();
    if (now > (circle_5_start + circle_5_delay)){
        circle_5_status = false;
    }

    now = millis();
    if (now > (circle_6_start + circle_6_delay)){
        circle_6_status = false;
    }

    now = millis();
    if (now > (circle_7_start + circle_7_delay)){
        circle_7_status = false;
    }

    now = millis();
    if (now > (circle_8_start + circle_8_delay)){
        circle_8_status = false;
    }

    now = millis();
    if (now > (circle_9_start + circle_9_delay)){
        circle_9_status = false;
    }

    now = millis();
    if (now > (circle_10_start + circle_10_delay)){
        circle_10_status = false;
    }

    now = millis();
    if (now > (circle_11_start + circle_11_delay)){
        circle_11_status = false;
    }

    // read sensors and update status
    int threshold = 700;                                    // The threshold should be lower if the user is wearing socks, or is a small child. For an adult: 1000.

    int button = 1;                                         // The number we will send to Processing if the sensor detects a touch
    long sensorValue = sensor_1.capacitiveSensor(30);       // Read the sensor value
    if (sensorValue > threshold) {                          // Touch detected
        if (circle_1_status == false){                      // if the circle is not active already
            circle_1_status = true;                         // activate
            circle_1_start = millis();                      // start the timer
            Serial.println(button);                         // Send message to serial port by the serial print
        }
    }
    button = 2;
    sensorValue = sensor_2.capacitiveSensor(30);
    if (sensorValue > threshold) {
        if (circle_2_status == false){
            circle_2_status = true;
            circle_2_start = millis();
            Serial.println(button);
        }
    }
    button = 3;
    sensorValue = sensor_3.capacitiveSensor(30);
    if (sensorValue > threshold) {
        if (circle_3_status == false){
            circle_3_status = true;
            circle_3_start = millis();
            Serial.println(button);
        }
    }
    button = 4;
    sensorValue = sensor_4.capacitiveSensor(30);
    if (sensorValue > threshold) {
        if (circle_4_status == false){
            circle_4_status = true;
            circle_4_start = millis();
            Serial.println(button);
        }
    }
    button = 5;
    sensorValue = sensor_5.capacitiveSensor(30);
    if (sensorValue > threshold) {
        if (circle_5_status == false){
            circle_5_status = true;
            circle_5_start = millis();
            Serial.println(button);
        }
    }
    button = 6;
    sensorValue = sensor_6.capacitiveSensor(30);
    if (sensorValue > threshold) {
        if (circle_6_status == false){
            circle_6_status = true;
            circle_6_start = millis();
            Serial.println(button);
        }
    }
    button = 7;
    sensorValue = sensor_7.capacitiveSensor(30);
    if (sensorValue > threshold) {
        if (circle_7_status == false){
            circle_7_status = true;
            circle_7_start = millis();
            Serial.println(button);
        }
    }
    button = 8;
    sensorValue = sensor_8.capacitiveSensor(30);
    if (sensorValue > threshold) {
        if (circle_8_status == false){
            circle_8_status = true;
            circle_8_start = millis();
            Serial.println(button);
        }
    }
    button = 9;
    sensorValue = sensor_9.capacitiveSensor(30);
    if (sensorValue > threshold) {
        if (circle_9_status == false){
            circle_9_status = true;
            circle_9_start = millis();
            Serial.println(button);
        }
    }button = 10;
    sensorValue = sensor_10.capacitiveSensor(30);
    if (sensorValue > threshold) {
        if (circle_10_status == false){
            circle_10_status = true;
            circle_10_start = millis();
            Serial.println(10);
        }
    }button = 11;
    sensorValue = sensor_11.capacitiveSensor(30);
    if (sensorValue > threshold) {
        if (circle_11_status == false){
            circle_11_status = true;
            circle_11_start = millis();
            Serial.println(button);
        }
    }

    // If Arduino doesn't print a neutral number, Processing will continue to play the last sound over and over again.
    Serial.println(0);

    display_leds();
}
