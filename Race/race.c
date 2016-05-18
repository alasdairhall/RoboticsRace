#include <stdio.h>
#include "sensing.h"

// int visited[][] = {
// 	{-1,1,-1,-1,-1},
// 	{-1,0,0,0,0},
// 	{-1,0,0,0,0},
// 	{-1,0,0,0,0},
// 	{-1,0,0,0,0}
// };

int orientation = 0; // 0 = North, 1 = East, 2 = South, 3 = West
int xPos = 1, yPos = 0;
int xTarget = 4, yTarget = 4;
int gridSize = 123; // 60 cm in ticks
int xTicks = 0, yTicks = 0;

void phase1(){
  moveForward();
  while(!(xPos == 1 && yPos == 0)){
    print("xPos: %d, yPos: %d\n",xPos,yPos);
    if (leftChecker1() == 0) {
     frontChecker1();
     rightChecker1();
     rotateRobot(2);
		moveForward();
	}
	else if (frontChecker1() == 0) {
     rightChecker1();
     rotateRobot(-1);
		moveForward();
	}
	else if (rightChecker1() == 0){
		moveForward();
	}
  else{
    rotateRobot(1);
    moveForward();
  }   
}  
  rotateRobot(2);  
}  

int minMove(int moves[]) {
	int min; // The best direction to rotate to. -1 to rotate left, 0 for no rotation, 1 to rotate right, 2 to 180
	if(moves[0] <= moves[1] && moves[0] <= moves[2]) {
		min = -1;
	} else if(moves[1] <= moves[0] && moves[1] <= moves[2]) {
		min = 0;
	} else {
		min = 1;
	}
  print("min: %d, moves[min+1]: %d\n", min, moves[min+1]);
	if(moves[min + 1] == 100) { // If the robot is at a dead end
		return 2;
	}
	return min;
}

void validateMoves(int clear[], int moves[]) {
	int i;
	for(i = 0; i < 3; i++) {
      print("i: %d, clear[i]: %d\n", i, clear[i]);
		if(clear[i] == 0) {
    print("i: %d\n", i);
			moves[i] = 100;
		}
	}
}

int inBoundMove(int pos, int change, int target) {
	int goal = xTarget + yTarget;
    return goal - (xPos + yPos + change);
}

void getMoves(int moves[]) {
	int even = orientation % 2 == 0;

	if(even) {
		moves[0] = inBoundMove(xPos,(orientation - 1),xTarget); // Different orientations will mean
		moves[1] = inBoundMove(yPos,(1 - orientation),yTarget); // that the way the x and y pos change
		moves[2] = inBoundMove(xPos,(1 - orientation),xTarget); // will be different
	} else {
		moves[0] = inBoundMove(yPos,(2 - orientation),yTarget);
		moves[1] = inBoundMove(xPos,(2 - orientation),xTarget);
		moves[2] = inBoundMove(yPos,(orientation - 2),yTarget);
	}
}

int getBestMove(int clear[]) {
	int moves[3]; // moves[0] stores left, moves[1] stores ahead, moves[2] stores right
	getMoves(moves);
	validateMoves(clear, moves);
	return minMove(moves);
}

void rotateRobot(int rotation) {
	turn(rotation);
	orientation = (orientation + rotation) % 4;
	if(orientation < 0) {
		orientation += 4;
	}
}

void moveForward() {
	moveForwardSquare(gridSize);
	if(orientation % 2 == 0) {
		//yTicks += (gridSize - orientation*gridSize);
		//yPos = yTicks / gridSize;
		yPos = yPos + (1 - orientation);
	} else {
		//xTicks += (2*gridSize - orientation*gridSize);
		//xPos = (xTicks / gridSize) + 1;
		xPos = xPos + (2 - orientation);
	}
}

void isClean(int walls[]) {
	// Checks if the blocks around are clear or not.
	if (frontChecker() == 1)
	{
				walls[1] = 0;
	}
	if (rightChecker() == 1)
	{
		walls[2] = 0;
	}
	if (leftChecker() == 1)
	{
		walls[0] = 0;
	}
}

void moveSquare() {
	// Checks for walls in all three directions
	int clear[] = {1,1,1}; //isclean(); // array storing whether or not there is a wall to the left, ahead and right respectively
	isClean(clear);
	int bestMove = getBestMove(clear);
	rotateRobot(bestMove);
	moveForward();
}

void goToTarget(int x, int y){
	xTarget = x; yTarget = y;
	while(!(xPos == xTarget && yPos == yTarget)) {
   print("xPos: %d, yPos: %d\n",xPos,yPos);
		moveSquare();
	}
}

int main() {
	//goToTarget(1,4);
	//goToTarget(4,4);
	//goToTarget(4,1);
	//goToTarget(1,0);
  
  //setSpeed(80);
  drive_setMaxSpeed(80);
  phase1();
  blink();
  goToTarget(4,4);
}
