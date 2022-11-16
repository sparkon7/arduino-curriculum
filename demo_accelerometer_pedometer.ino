//  File:  demo_accelerometer_pedometer.ino
//
//  Use the accelerometer on a Circuit Playground Express to count steps.
//    * Use exponential smoothing to reduce noise in the total acceleration value
//    * Determine a resting offset value for acceleration at startup
//    * Count steps when acceleration minus resting offset is above a threshold
//
//   The step-counting algorithm has to determine when the acceleration is above a
//   threshold and also whether the acceleration has fallen below the threshold.
//   Details are in the step_count() fiunction
//
//   Note to user:  You may need to experiment with the value of aStepThreshold
//   in the loop() function.  The value of aStepThreshold is the value of acceleration
//   (relative to baseline) that we assume is caused by a step motion.  If aStepThreshold
//   is too low, then simple body movements, e.g. shifting weight in a chair, might be
//   counted as a step.  If aStepThreshold is too high, the movement of a step might
//   not be counted as a step.
//
//  Gerald Recktenwald, gerry@pdx.edu,  2022-06-16

#include <Adafruit_CircuitPlayground.h>

float aOffset;
unsigned long tStart;
boolean DEBUG_PRINT = false;

// ------------------------------------------------------------------------------------
void setup() {
  float aSum;            //  Store accumulated sum during baseline calculation
  int   nave=500;        //  Number of readings used to obtain the baseline
  int   baseDelay=10;    //  Time in milliseconds to wait between baseline readings
  
  Serial.begin(115200);
  CircuitPlayground.begin();
  delay(3000);         // Pause for system startup.  This may not be necessary
  
  // -- Compute a baseline level of acceleration.  Normally the user would be
  //    standing still during this time.  So, baseline level should be (roughly)
  //    the acceleration of gravity, g = 9.8 m/s^2.  Steps are determined by
  //    measuring the acceleration relative to the baseline level.
  //    Determine the baseline as the average of nave readings
  Serial.print("Calibrating for ");  Serial.print(nave*baseDelay/1000); Serial.println(" seconds");
  aSum = 0.0;
  for ( int i=1; i<=nave; i++ ) {
    aSum += accelSmooth(0.5,DEBUG_PRINT);
    delay(baseDelay);
  }
  aOffset = aSum / float(nave);
  Serial.println("Done calibrating");
  Serial.print("aOffset = ");  Serial.print(aOffset);  Serial.println(" m/s^2");
  delay(1000);
  Serial.println("t\ta\tnstep");

  tStart = millis();      //  This is the true start time after set-up housekeeping
}

// ------------------------------------------------------------------------------------
void loop() {
  float a, aStepThreshold=1.0, tNow;
  static unsigned int nSteps=0;                 //  Static variables retain state, no need to use global
  
  tNow = float(millis() - tStart) / 1000.0;     //  Time in seconds since the start
  a = accelSmooth(0.5,DEBUG_PRINT) - aOffset;   //  Total acceleration relative to stationary
  nSteps += count_step(a, aStepThreshold);      //  Add to step count if a step was detected

  Serial.print(tNow);
  Serial.print("\t");
  Serial.print(a);
  Serial.print("\t");
  Serial.println(nSteps);
  
  delay(100);
}

// ------------------------------------------------------------------------------------
//  Given the current acceleration and a threshold value for acceleration return 1 if
//  a step was likely (according to the decision rules) or 0 otherwise.  The threshold
//  value is determined by experimentation.  A good start for the threshold is about 1 m/s^2
//
int count_step(float a, float threshold) {

  int n;                            //  Local variable, number of steps detected: 1 or 0
  static boolean lastWasLow=true;   //  Was the last acceleration level was above the threshold?

  n = 0;
  if ( a>threshold  ) {      //  A step occurred if accleration was above the threshold
    if ( lastWasLow ) {      //  AND if the last acceleration value was NOT above the threshold
      n = 1;
    }
    lastWasLow = false;      //  Threshold was crossed, so last step was not low
  } else {
    lastWasLow = true;       //  Threshold was not crossed, so last step was low
  }
  return(n);
}

// ------------------------------------------------------------------------------------
//  Make a new measurement of total acceleration and return the exponentially-weighted
//  average of this measurement and recent measurements.
//  The smoothing acts as a low-pass filter to reduce high frequency noise.
//  The smoothing parameter is alfa:  0 < alfa <= 1.0.  When alfa = 1, no smoothing
//  is applied -- the most recent reading of total acceleration is returned.
//  As alfa is reduced toward zero more smoothing is applied. You will need to
//  experiment to determine a value of alfa that works with the acceleration you
//  are measuring.  A value in the range 0.3 < alfa < 0.6 is a usually first guess.
//
float accelSmooth(float alfa, boolean printDetail) {
  float ax, ay, az, aTot, aTotSmooth;   //  acceleration components and magnitude measured by the sensor
  static float aTotOld=-99.0;           //  Value retained for the next call to accelSmooth

  // -- Retrieve acceleration components and compute the total
  ax = CircuitPlayground.motionX();
  ay = CircuitPlayground.motionY();
  az = CircuitPlayground.motionZ();
  aTot = sqrt(ax*ax + ay*ay + az*az);         //  could also use pow(ax,2), but ax*ax is faster

  // -- Use exponential smoothing of the total acceleration value (magnitude of acceleration vector).
  //    The "if" statement tests whether this is the first measurement.  aTotOld is initialized
  //    to -99 because for the very first measurement, there is no true "old" value, and
  //    we simply use the current reading.  This test avoids causing the exponential average to
  //    include a bogus intial reading.  Without this test the first few values returned by
  //    this (accelSmooth) function would include a reading of zero, which would cause
  //    the trend in values to start at an artificially low value.
  if ( aTotOld<0.0 ) {  // Don't smooth if this is first measurement because we don't have true "old" value
    aTotSmooth = aTot;
  } else {
    aTotSmooth = aTot*alfa + (1-alfa)*aTotOld;
  }
  aTotOld = aTotSmooth;  //  Save for next measurement

  // -- Print acceleration values without extra text so that Serial Plotter can be used
  //    When everything is working, there is no need to print these details
  if ( printDetail ) {
    Serial.print(ax);
    Serial.print("\t");   Serial.print(ay);
    Serial.print("\t");   Serial.print(az);  
    Serial.print("\t");   Serial.print(aTot);
    Serial.print("\t");   Serial.println(aTotSmooth);
  }

  return(aTotSmooth);
}
