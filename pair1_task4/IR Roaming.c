/*
  IR Roaming.c

  Use IR LED and IR receiver pairs as object detectors for robot roaming.

  http://learn.parallax.com/activitybot/roaming-infrared-flashlights
*/

#include "simpletools.h"                        // Library includes
#include "abdrive.h"
#include "ping.h" 

int irLeft, irLeft;                            // IR variables

int main()                                      // Main function
{
  low(26);                                      // D/A0 & D/A1 to 0 V
  low(27);
  int distance;

  drive_setRampStep(12);                        // Max step 12 ticks/s every 20 ms

  while(1)
  {
    freqout(11, 1, 38000);                      // Check left objects
    irLeft = input(10);

    distance = ping_cm(8);

    if(distance > 5 && irLeft == 1)             // No obstacles?
    {    
      drive_rampStep(20, 40);
    }
    else if (distance > 5 && irLeft == 0)       // Something to the Left?
    {
      drive_rampStep(40, 20);               // ...turn left
    }
    else if (distance <= 5)
    {
      drive_rampStep(0, 0);
    }      
  }
}

