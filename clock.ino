#include <Adafruit_CircuitPlayground.h>



void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 CircuitPlayground.begin();  //  This .begin() is important for consistent button behavior
}

unsigned long time1 = 0;
unsigned long sec = 0;
unsigned long ctr = 0;
int hours = 23;
int minutes = 59;
void loop() {
  time1 = millis();
  sec = (unsigned long) ((time1/1000)-(ctr * 60));
  
  if(hours<10){
    Serial.print(0);
    }
  Serial.print(hours);
  Serial.print(":");
  if(minutes<10){
    Serial.print(0);
    }
  Serial.print(minutes);
  
  Serial.print(":");
  if(sec<10){
    Serial.print(0);

    
    
    
    
    }
  Serial.print(sec);
  Serial.print("\n");
  
  sec += 1;
  if(sec == 60){
    minutes+=1;
    sec = 0;
    ctr++;
    if(minutes == 60){
      minutes = 0;
      hours += 1;
      if(hours == 24){
        hours = 0;  
      }
    }
  }
}
