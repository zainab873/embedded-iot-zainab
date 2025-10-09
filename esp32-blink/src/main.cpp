#include <Arduino.h> 
#define LED_PIN 2


#ifndef LED_BUILTIN

  #define LED_BUILTIN 2
#endif

const bool ACTIVE_LOW = false;    //this is a flag


void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_BUILTIN, ACTIVE_LOW ? HIGH : LOW); // turn the LED off (HIGH is the voltage level)
}

void loop() {
     static bool on = false;

     on = !on;
     digitalWrite(LED_BUILTIN,(on ^ ACTIVE_LOW) ? HIGH : LOW); // turn the LED on (LOW is the voltage level )
      delay(500); // wait for a second



}
