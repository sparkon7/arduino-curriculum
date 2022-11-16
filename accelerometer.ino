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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  CircuitPlayground.begin();
  setupOLED();
}

void loop() {
  // put your main code here, to run repeatedly:
  float x, y, z, total;
  x = CircuitPlayground.motionX();
  y = CircuitPlayground.motionY();
  z = CircuitPlayground.motionZ();
  total = sqrt(x*x + y*y + z*z);
  serial_print(x, y, z, total);

   OLED.clearDisplay();
   OLED.setTextSize(1);
   OLED.setCursor(0,0);
   OLED.print(F("X: = "));
   OLED.print(x);
   OLED.setCursor(0,12);
   OLED.print(F("Y: = "));
   OLED.print(y);
   OLED.setCursor(0,24);
   OLED.print(F("Z: = "));
   OLED.print(z);
   OLED.setCursor(0,36);
   OLED.print(F("Total: = "));
   OLED.print(total);
   OLED.display();

   if(x < -1){
    for(int i = 0; i < 5; i++){
      CircuitPlayground.setPixelColor(i, 0, 0, 0);
    }
    for(int i = 5; i < 10; i++){
      CircuitPlayground.setPixelColor(i, 255, 255, 255);
    }
   }else if(){
    
   }else{
      for(int i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i, 255, 255, 255);
    }
    }
  delay(250);
}

void serial_print(float x, float y, float z, float total){
  Serial.print("X: ");
  Serial.print(x);
  Serial.print("   Y: ");
  Serial.print(y);
  Serial.print("   z: ");
  Serial.print(z);
  Serial.print("\n");
  Serial.print("Total: ");
  Serial.print(total);
  Serial.print("\n");
  
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
