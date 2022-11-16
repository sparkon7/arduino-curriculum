//  File:  click_button_count.ino
//
//  Use an interrupt to catch button status on a Circuit Playground Express.
//  Count and print the number of times the button has been pressed.

#include <Adafruit_CircuitPlayground.h>

//    Assign click_button to left or right to see the difference
//
int  click_button = CPLAY_LEFTBUTTON;
// int  click_button = CPLAY_RIGHTBUTTON;

// Note:  click_button needs to be global if it is accessed in setup() and loop()
//        toggle_on and button_count need to be global because they are accessed in loop()
//        and assigned in handle_click

int toggle_on = false;     //  Saved state flag
int button_count = 0;      //  Number of times the button has been pressed

// ------------------------------------------------------------------------
//   Interrupt and Serial Monitor are configured in setup()
//
void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();  //  This .begin() is important for consistent button behavior

  // -- Register the interrupt handler (handle_click) and mode (RISING)
  attachInterrupt( digitalPinToInterrupt(click_button), handle_click, RISING);
}

// ------------------------------------------------------------------------
//   loop() uses global variables but does not assign values to them:
//      toggle_on indicates the state
//      button_count tells how many times the button has been pressed
//   The interrupt handler, handle_click, changes the value of toggle_on
//   and button_count when a debounced interrupt is detected
//
void loop() {
  Serial.print(toggle_on);
  //==== Write code under this line ====

  //Serial.print( digitalRead(click_button) );  //  Shows that "on" state is temporary
  //Serial.print("   ");
  //Serial.println(button_count);
}

// ------------------------------------------------------------------------
//   handle_click() is the interrupt handler.  (a.k.a. "ISR" in Arduino documentation.
//   handle_click() responds to button clicks and updates toggle_on and button_count.
//   By keeping track of the time between button clicks, handle_click avoids spurious
//   events due to high speed mechanical bouncing of the button
//
void  handle_click()
{
  static unsigned long last_interrupt_time = 0;       //  Zero only when code first runs
 
  unsigned long interrupt_time = millis();             //  Read the clock
  if ( interrupt_time - last_interrupt_time > 200 ) {  //  Only count clicks separated by 200 msec
    toggle_on = !toggle_on;
    button_count++;
  }
  last_interrupt_time = interrupt_time;
}
