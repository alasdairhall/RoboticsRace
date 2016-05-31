#include "sensing.h"
#include "simpletools.h"
#include "abdrive.h"
#include "ping.h"

#define GRID_SIZE 400
#define SENSOR_VALUE 14
#define MULTIPLIER 2
#define IR_LEFT 10
#define IR_RIGHT 10
#define BASE_SPEED_TICKS 64
#define ROBOT_WIDTH 105.8

int irLeft, irRight;

void blink() {
  int i;
  for(i = 0; i < 3; i++)
  {
    high(26);
    pause(500);
    low(26);
    pause(500);
  }
  pause(1000);
}

void setSpeed(int speed)
{
  drive_speed(speed,speed);
}

void turn(int direction)
{
  if (direction == -1)
  {
    drive_goto(-25,26);
  }
  else if (direction == 1)
  {
    drive_goto(26,-25);
  }
  else if (direction == 2)
  {
    drive_goto(51,-51);
  }
}

int getIR()
{
    irLeft = 0;
    irRight = 0;
    for (int dacVal = 0; dacVal < 160; dacVal += 8) {
        dac_ctr(26, 0, dacVal);
        freqout(11, 1, 38000);
        irLeft += input(10);

        dac_ctr(27, 1, dacVal);
        freqout(1, 1, 38000);
        irRight += input(2);
    }
}

double calcDistance(int current, int prev) {
  return (current - prev) * 3.25;
}

void moveForwardSquare()
{
  double xDist = 0;
  double yDist = 0;
  double angle = 0;
  double distance = 0;

  int prevTicksLeft = 0;
  int prevTicksRight = 0;

  drive_getTicks(&prevTicksLeft, &prevTicksRight);
  while(distance < GRID_SIZE) {
      getIR();
      int changeVal;
      if(irLeft < SENSOR_VALUE && irRight < SENSOR_VALUE){ // Wall either side
          changeVal = (irLeft - irRight) * MULTIPLIER;
      } else if ( irLeft < SENSOR_VALUE ) { // Wall to the left
          changeVal = (irLeft - IR_LEFT) * MULTIPLIER;
      } else if ( irRight < SENSOR_VALUE ) { // Wall to the right
          changeVal = (IR_RIGHT - irRight) * MULTIPLIER;
      } else { // If no walls to the side, carry on as normal
          changeVal = 0;
      }

      drive_speed(BASE_SPEED_TICKS - changeVal, BASE_SPEED_TICKS + changeVal); // Set the new drive speed with the new changeVal

      int ticksLeft, ticksRight;
      drive_getTicks(&ticksLeft,  &ticksRight); // get current ticks count

      // calculate distances
      double distRight = calcDistance(ticksRight, prevTicksRight); // Distance of left wheel
      double distLeft = calcDistance(ticksLeft, prevTicksLeft); // Distance of right wheel
      double distCentre = (distRight + distLeft) / 2; // The average of the left and right distance
      angle = angle + (distRight - distLeft) / ROBOT_WIDTH;
      // update prevTicks
      prevTicksLeft = ticksLeft;
      prevTicksRight = ticksRight;

      xDist = xDist + distCentre * cos(angle);
      yDist = yDist + distCentre * sin(angle);
      distance = sqrt(xDist*xDist + yDist*yDist); // work out distance travelled using pythagoras
  }
  drive_speed(0,0);
}

void correct() {
  if(ping_cm(8) < 14) { // if too close, move back
    while(ping_cm(8) < 14) {
      drive_speed(-10,-10);
      pause(10);
    }
  } else {
    while(ping_cm(8) > 14) { // if too far, move forward
      drive_speed(10,10);
      pause(10);
    }
  }
  drive_speed(0,0);
}

int frontChecker()
{
  int result;
  int distance = ping_cm(8);
  if (distance < 35)
  {
    correct();
    return 1;
  }
  else
  {
    return 0;
  }
}

int rightChecker()
{
    turn(1);
    int val = frontChecker();
    turn(-1);
    return val;
}

int leftChecker()
{
    turn(-1);
    int val = frontChecker();
    turn(1);
    return val;
}

int leftChecker1() {
  rotateRobot(-1);
  return frontChecker();
}

int frontChecker1() {
  rotateRobot(1);
  return frontChecker();
}

int rightChecker1() {
  rotateRobot(1);
  return frontChecker();
}
