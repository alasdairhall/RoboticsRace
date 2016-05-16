#include "simpletools.h"                        // Library includes
#include "abdrive.h"
#include "ping.h"
#include "logging.h"

int lTicks[] = {0, 0};
int rTicks[] = {0, 0};
double angle = 0;
int irLeft, irLeft;
double runningAngle = 0, runningX = 0, runningY = 0;
int inProgress = 1;

void updateValues(double lDist, double rDist) {
  if( angle > (2 * 3.14159) - 0.5 || angle < 0.05 ) {
    runningAngle += 0;
    runningX += calcXChangeStraight(lDist, runningAngle);
    runningY += calcYChangeStraight(lDist, runningAngle);
  } else {
    runningAngle += angle;
    double midRad = calcMidRad(lDist, rDist, angle);
    runningX += calcXChangeAngle(midRad, angle);
    runningY += calcYChangeAngle(midRad, angle, runningAngle);
  }
}

void normaliseAngle() {
  if (runningAngle < 0) {
      runningAngle += 2*3.14159;
    } else if (runningAngle > 2 * 3.14159) {
      runningAngle -= 2*3.14159;
    }
}

void followWall() {
    freqout(11, 1, 38000);                      // Check left objects
    irLeft = input(10);
    int distance;

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
      inProgress = 0;
    }
}     

int main()                                      // Main function
{
  drive_setRampStep(12);                        // Max step 12 ticks/s every 20 ms
  
  low(26);                                      // D/A0 & D/A1 to 0 V
  low(27);
  
  while(inProgress)
  {         
    followWall();
    lTicks[0] = lTicks[1];
    rTicks[0] = rTicks[1];
    
    drive_getTicks(&lTicks[1], &rTicks[1]);
    
    // Work out the distance travelled by the left wheel, right wheel and the angle changed since the last check
    double lDist = ticksToDistance(lTicks[1]-lTicks[0]);
    double rDist = ticksToDistance(rTicks[1]-rTicks[0]); 
    angle = calcAngle(lDist, rDist);
    
    updateValues(lDist, rDist); // Update all of the running values
    
    //normaliseAngle(); // Keeps the angle between 0 and 2 Pi 
  }
  drive_speed(0,0);
  
  drive_rampStep(0, 0);
 // print("Distance from starting point: %f, At an angle of: %f\n", calcHyp(runningX, runningY) / 10, toDegrees(calcFinalAngle(runningX, runningY)));
 print("Distance from starting point: %f, At an angle of: %f\n", calcHyp(runningX, runningY) / 10, toDegrees(runningAngle));
}
  