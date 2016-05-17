#include "sensing.h"
#include "simpletools.h"
#include "abdrive.h"
#include "ping.h"

int irLeft, irLeft;

void setSpeed(int speed)
{
  drive_speed(speed,speed);
}

void turn(int direction)
{
  if (direction == -1)
  {
    drive_goto(-26,26);
  }
  else if (direction == 1)
  {
    drive_goto(26,-26);
  }
  else if (direction == 2)
  {
    drive_goto(51,-51);
  }
}

void moveForwardSquare(int length)
{
  drive_goto(length,length);
}

int frontChecker()
{
  int result;
  distance = ping_cm(8);
  if (distance < 10)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int rightChecker()
{
    freqout(11, 1, 38000);                      // Check left objects
    irRight = input(10);
    if (irRight == 1)
    {
      return 1;
    }
    else
    {
      return 0;
    }
}

int leftChecker()
{
    freqout(11, 1, 38000);                      // Check left objects
    irLeft = input(10);
    if (irLeft == 1)
    {
      return 1;
    }
    else
    {
      return 0;
    }
}
