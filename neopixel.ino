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

  int nPixel = 3 ;   //  Number of NeoPixel to turn on and off
  int iRed = 200;   //  Amount of red to display.    0 <= iRed <= 255
  int iGreen = 0;   //  Amount of green to display.  0 <= iGreen <= 255
  int iBlue = 0;    //  Amount of blue to display.   0 <= iBlue <= 255

  CircuitPlayground.setPixelColor(nPixel, iRed, iGreen, iBlue);   // turn on
  delay(500);                                                    // wait 
  CircuitPlayground.setPixelColor(nPixel, 0, 0, 0);               // turn off
  delay(500);                                                    // wait 

  CircuitPlayground.setPixelColor(6, 0, 0, 0);  
  delay(500);
  CircuitPlayground.setPixelColor(6, 0, 0, 200);               // turn off
  delay(500);

  CircuitPlayground.setPixelColor(0, 0, 0, 0);  
  delay(500);
  CircuitPlayground.setPixelColor(0, 100, 0, 100);               // turn off
  delay(500);

  CircuitPlayground.setPixelColor(1, 0, 0, 0);  
  delay(500);
  CircuitPlayground.setPixelColor(1, 100, 50, 100);               // turn off
  delay(500);

  CircuitPlayground.setPixelColor(2, 0, 0, 0);  
  delay(500);
  CircuitPlayground.setPixelColor(2, 0, 200, 0);               // turn off
  delay(500);

  CircuitPlayground.setPixelColor(4, 0, 0, 0);  
  delay(500);
  CircuitPlayground.setPixelColor(4, 200, 75, 150);               // turn off
  delay(500);
  
  CircuitPlayground.setPixelColor(5, 0, 0, 0);  
  delay(500);
  CircuitPlayground.setPixelColor(5, 0, 200, 0);               // turn off
  delay(500);

  CircuitPlayground.setPixelColor(7, 0, 0, 0);  
  delay(500);
  CircuitPlayground.setPixelColor(7, 200, 75, 150);               // turn off
  delay(500);
  
   CircuitPlayground.setPixelColor(8, 0, 0, 0);  
  delay(500);
  CircuitPlayground.setPixelColor(8, 34, 120, 50);               // turn off
  delay(500);

  CircuitPlayground.setPixelColor(9, 0, 0, 0);  
  delay(500);
  CircuitPlayground.setPixelColor(9, 255, 12, 1);               // turn off
  delay(500);
}
