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
  OLED.clearDisplay();
  OLED.setCursor(54,32);
  OLED.setTextSize(1);
  OLED.print("Hello.");
  OLED.display();
  delay(1000);
  OLED.clearDisplay();
}


void loop(){
  
}
