//  File:  BlinkNeoPixel.ino
//
//  Turn on a NeoPixel on for one second, then off for one second, repeatedly.
//  The NeoPixel is specified by the nPixel variable in the loop() function.
//
//  Reference:  https://learn.adafruit.com/circuit-playground-lesson-number-0/neopixels

#include <Adafruit_CircuitPlayground.h>


// -- The setup function runs only once after power is first applied or reset
void setup() {
  CircuitPlayground.begin();
}

// -- The loop function runs over and over again forever
void loop() {
  int nPixel = 3;   //  Number of NeoPixel to turn on and off
  int iRed = 200;   //  Amount of red to display.    0 <= iRed <= 255
  int iGreen = 200;   //  Amount of green to display.  0 <= iGreen <= 255
  int iBlue = 200;
   for(int i = 0; i< 10; i++){
    CircuitPlayground.setPixelColor(i, iRed, iGreen, iBlue);
    delay(100);
  }
}
