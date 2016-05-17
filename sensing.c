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

void moveSquare(int length)
{
  drive_goto(length,length);
}

int getIR() {
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
