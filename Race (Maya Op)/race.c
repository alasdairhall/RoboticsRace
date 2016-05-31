#include <stdio.h>
#include "sensing.h"

int values[5][5] = {
	{100,100,100,100,100},
	{ 7 , 6 , 5 , 4 , 3 },
	{100, 5 , 4 , 3 , 2 },
	{100, 4 , 3 , 2 , 1 },
	{100, 3 , 2 , 1 , 0 }
};

int orientation = 0; // 0 = North, 1 = East, 2 = South, 3 = West
int xPos = 1, yPos = 0;
int xTarget = 4, yTarget = 4;
int xTicks = 0, yTicks = 0;
int deadEnd = 0;

void checkDeadEnd(int wallNum) {
	if(deadEnd) {
    	if(wallNum > 1) {
    		values[xPos][yPos] = 100;
    	} else {
    		deadEnd = 0;
    	}
    }
}

//rows*columns*orientation. the walls on the sides are already initialised as 0.
// int arr[5][5][4] = {
// 	{{-1,-1,1,0},{-1,-1,0,-1},{-1,-1,0,-1},{-1,0,0,-1}}
// 	{{-1,-1,-1,0},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,0,-1,-1}},
// 	{{-1,-1,-1,0},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,0,-1,-1}},
// 	{{0,-1,-1,0},{0,-1,-1,-1},{0,-1,-1,-1},{0,0,-1,-1}},
// }
int arr[5][5][4] = {
	//ROW: 0             1             2             3             4           COL:
	{{-1, 0,-1,-1},{-1, 0,-1,-1},{-1, 0,-1,-1},{-1, 0,-1,-1},{-1, 0,-1,-1}}, // 0
	{{ 1, 0, 0, 0},{-1,-1, 1, 0},{-1,-1,-1, 0},{-1,-1,-1, 0},{ 0,-1,-1, 0}}, // 1
	{{ 0,-1,-1, 0},{-1,-1, 0,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{ 0,-1,-1,-1}}, // 2
	{{ 0,-1,-1,-1},{-1,-1, 0,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{ 0,-1,-1,-1}}, // 3
	{{ 0,-1,-1,-1},{-1, 0, 0,-1},{-1, 0,-1,-1},{-1, 0,-1,-1},{ 0, 0,-1,-1}} //  4
}

void phase1(){
  moveForward();
  while(!(xPos == 1 && yPos == 0)){
    print("xPos: %d, yPos: %d\n",xPos,yPos);
    int noOfWalls = 0;
    arr[xPos][yPos][(orientation+2)%4] = 1; // must be clear behind because has come from that direction
    if (leftChecker1() == 0) {
    	arr[xPos][yPos][orientation] = 1
		int front = frontChecker1();
		arr[xPos][yPos][orientation] = (front + 1) % 2; // because we represent a wall as a 0 in the array but frontchecker returns 1 if there is a wall
		int right = rightChecker1();		
		arr[xPos][yPos][orientation] = (right + 1) % 2;
    	
    	noOfWalls = front + right;
    	checkDeadEnd(noOfWalls);
    	rotateRobot(2);
		moveForward();
	}
	else if (frontChecker1() == 0) {
		arr[xPos][yPos][(orientation+3)%4] = 0;
		arr[xPos][yPos][orientation] = 1;
		right = rightChecker1();
		arr[xPos][yPos][orientation] = (right + 1) % 2;

		noOfWalls = 1 + right;
		checkDeadEnd(noOfWalls);
	    rotateRobot(-1);
		moveForward();
	}
	else if (rightChecker1() == 0){
		arr[xPos][yPos][orientation] = 1;
		arr[xPos][yPos][(orientation+2)%4] = 0;
		arr[xPos][yPos][(orientation+3)%4] = 0;
		checkDeadEnd(2);
		moveForward();
	}
  else{
  		arr[xPos][yPos][orientation] = 0;
		arr[xPos][yPos][(orientation+2)%4] = 0;
		arr[xPos][yPos][(orientation+3)%4] = 0;
  	if(!(xPos == 4 && yPos == 4)) { // If it's at a dead end it wants to remember to not come down here, unless it is the finishing square
  		deadEnd = 1;
    	values[xPos][yPos] = 100;
  	}
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
		moves[0] = values[xPos + (orientation - 1)][yPos]; // Different orientations will mean
		moves[1] = values[xPos][yPos + (1 - orientation)]; // that the way the x and y pos change
		moves[2] = values[xPos + (1 - orientation)][yPos]; // will be different
	} else {
		moves[0] = values[xPos][yPos + (2 - orientation)];
		moves[1] = values[xPos + (2 - orientation)][yPos];
		moves[2] = values[xPos][yPos + (orientation - 2)];
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
	moveForwardSquare();
	if(orientation % 2 == 0) {
		yPos = yPos + (1 - orientation);
	} else {
		xPos = xPos + (2 - orientation);
	}
}

void isClean(int clear[]) {
	// Checks if the blocks around are clear or not.
	if (arr[xPos][yPos][orientation] == -1) {
		if (frontChecker() == 1) {
					clear[1] = 0;
		}
	} else if (arr[xPos][yPos][orientation] == 0) {
			clear[1] = 0;
	} else {
		clear[1] = 1;
	}

	if (arr[xPos][yPos][(orientation+1)%4] == -1) {
		if (rightChecker() == 1) {
			clear[2] = 0;
		}
	} else if (arr[xPos][yPos][(orientation+1)%4] == 0) {
			clear[2] = 0;
	} else {
		clear[2] = 1;
	}

	if (arr[xPos][yPos][(orientation+3)%4] == -1) {
		if (leftChecker() == 1) {
			clear[0] = 0;
		}
	} else if (arr[xPos][yPos][(orientation+3)%4] == 0) {
			clear[0] = 0;
	} else {
		clear[0] = 1;
	}
	//the else blocks are excess. You can get rid of it if you want, just put it there to make it more clear.
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
