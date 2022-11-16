//  File:  print_light_sensor.ino
//
//  Measure ambient light levels with the light sensor built into
//  the Circuit Playground.  Print the value returned by the light
//  sensor and print a message ("it's dark") if the reading is
//  below a user-defined threshold

// -- Include functions provided by the Circuit Playground library
#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
// ----------------------------------------------------------------
void setup() {
  Serial.begin(9600);        //  Start connection to Serial Monitor
  CircuitPlayground.begin(); //  Start built-in functions of CP
  pinMode(A2, OUTPUT);
}

// ----------------------------------------------------------------
void loop() {

  int value;             //  reading of the light sensor
  int nPixel = 3;       //  Number of NeoPixel to turn on and off
  int iRed = 0;         //  Amount of red to display.    0 <= iRed <= 255
  int iGreen = 250;     //  Amount of green to display.  0 <= iGreen <= 255
  int iBlue = 0;        //  Amount of blue to display.   0 <= iBlue <= 255
  // -- Read the light sensor:   0 <= value <= 1023
  value = CircuitPlayground.lightSensor();

  // -- Print light level readings
  Serial.print("Light Sensor: ");
  Serial.print(value);
  Serial.print("\n");

  
  //    CircuitPlayground.setPixelColor(nPixel, iRed, iGreen, iBlue);
  // <= less than or equal to
  // < less than
  // >= greater than or equal to
  // > greater than
  // == equal to
  // != not equal to
  // =================  ADD CODE HERE ====================
  
  if(value < 20){
    for(int i = 2; i < 9; i++)
      CircuitPlayground.setPixelColor(i, 0, 0, 0);
    }
  else if (25 < value && value < 50){
        for(int i = 2; i < 9; i++)
      CircuitPlayground.setPixelColor(i, 20, 20, 20);
  }else{
        for(int i = 2; i < 9; i++)
      CircuitPlayground.setPixelColor(i, 255, 255, 255);
  }
  makeTone(A2, 600, 150);
  delay(2000);
}

void makeTone (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds) {
  int x;   
  long delayAmount = (long)(1000000/frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
  for (x=0; x<loopTime; x++) {        // the wave will be symetrical (same time high & low)
     digitalWrite(speakerPin,HIGH);   // Set the pin high
     delayMicroseconds(delayAmount);  // and make the tall part of the wave
     digitalWrite(speakerPin,LOW);    // switch the pin back to low
     delayMicroseconds(delayAmount);  // and make the bottom part of the wave
  }  
}
