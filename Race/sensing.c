#include "sensing.h"
#include "simpletools.h"
#include "abdrive.h"
#include "ping.h"

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

void correctBack() {
  while(ping_cm(8) < 14) {
    drive_speed(-5,-5);
  }   
  drive_speed(0,0);
}

void correctFront() {
  print("WHY DON'T I WORK");
  while(ping_cm(8) > 16) {
    drive_speed(5,5);
  }    
  drive_speed(0,0);
} 

int frontChecker()
{
  int result;
  int distance = ping_cm(8);
  if (distance < 30)
  {
    if (distance < 10) {
      correctBack();
    } else {
      correctFront();
    }           
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

  