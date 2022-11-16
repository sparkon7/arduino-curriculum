//  File:  print_light_sensor.ino
//
//  Measure ambient light levels with the light sensor built into
//  the Circuit Playground.  Print the value returned by the light
//  sensor and print a message ("it's dark") if the reading is
//  below a user-defined threshold

// -- Include functions provided by the Circuit Playground library
#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>               //  Wire.h provides I2C support
#include <Adafruit_GFX.h>       //  Generic graphics library: fonts, lines, effects
#include <Adafruit_SSD1306.h>   //  Library for the micro OLED display
#include <Adafruit_CircuitPlayground.h> 

// -- Create an SSD1306 object called OLED that is connected by I2C
#define OLED_RESET      4  // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_WIDTH  128  // OLED display width in pixels
#define SCREEN_HEIGHT  64  // OLED display height in pixels
#define I2CADDR  0x3D      // I2C address is used in setupOLED()
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);   // The CP microcontroller pin for the speaker

// ----------------------------------------------------------------
void setup() {
  Serial.begin(9600);        //  Start connection to Serial Monitor
  CircuitPlayground.begin(); //  Start built-in functions of CP
  
  setupOLED(); 
}

// ----------------------------------------------------------------
void loop() {
  int value;             //  reading of the light sensor
  int nPixel = 3;       //  Number of NeoPixel to turn on and off
  int iRed = 250;         //  Amount of red to display.    0 <= iRed <= 255
  int iGreen = 250;     //  Amount of green to display.  0 <= iGreen <= 255
  int iBlue = 250;        //  Amount of blue to display.   0 <= iBlue <= 255
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
  if(value < 30){
    for(int i = 2; i < 10; i++){
      CircuitPlayground.setPixelColor(i, iRed, iGreen, iBlue);
    }
    
  }else{
  for(int i = 9; i > -1; i--)
      CircuitPlayground.setPixelColor(i, 0, 0, 0);
   
  }
   delay(1000);
}




void setupOLED() {
  
    // -- Set up OLED display.  Use internal 3.3v supply, and Adafruit trick
    //      SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    //    I2C address is 0x3C for the 128x32 display
    if ( !OLED.begin(SSD1306_SWITCHCAPVCC, I2CADDR) ) {
      Serial.println(F("SSD1306 allocation failed"));
      while (true) ;   // Don't proceed, loop forever
    }
  
    // -- Show Adafruit splash screen stored in image buffer.
    OLED.display();
    delay(1000);         //  Pause to allow user to read the display
    
    // -- Clear the splash screen, set default text mode and display a "ready" message.
    OLED.clearDisplay();
    OLED.setTextSize(1);
    OLED.setTextColor(SSD1306_WHITE);
    OLED.print(F("OLED is ready"));
    OLED.display();
    delay(1000);                         //  Pause to allow user to read the display
  }
