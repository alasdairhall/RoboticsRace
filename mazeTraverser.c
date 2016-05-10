#include <stdio.h>

int visited[][] = {
	{-1,1,-1,-1,-1},
	{-1,0,0,0,0},
	{-1,0,0,0,0},
	{-1,0,0,0,0},
	{-1,0,0,0,0}
};

int orientation = 0; // 0 = North, 1 = East, 2 = South, 3 = West

int xPos = 1, yPos = 0;
int xTarget = 4, yTarget = 4;

int minMove(int moves[]) {
	int min; // The best direction to rotate to. -1 to rotate left, 0 for no rotation, 1 to rotate left, 2 to 180
	if(moves[0] <= moves[1] && moves[0] <= moves[1]) {
		min = -1
	} else if(moves[1] <= moves[0] && moves[1] <= moves[2]) {
		min = 0;
	} else {
		min = 1;
	}

	if(moves[min + 1] == -1) { // If the robot is at a dead end
		return 2;
	}
	return min;
}

void validateMoves(int clear[], int moves[]) {
	int i;
	for(i = 0; i < 3; i++) {
		if(!clear[i]) {
			moves[i] = -1;
		}
	}
}

void getMoves(int moves[]) {
	int even = orientation % 2 == 0;
	int goal = xTarget + yTarget;
	
	if(even) {
		moves[0] = goal - ((xPos + (orientation - 1)) + yPos); // Different orientations will mean
		moves[1] = goal - (xPos + (yPos + (1 - orientation))); // that the way the x and y pos change
		moves[2] = goal - ((xPos + (1 - orientation)) + yPos); // will be different
	} else {
		moves[0] = goal - (xPos + (yPos + (2 - orientation)));
		moves[1] = goal - (xPos + (2 - orientation)) + yPos));
		moves[2] = goal - (xPos + (yPos + (orientation - 2)));
	}
}

int getBestMove(int clear[]) {
	int moves[3]; // moves[0] stores left, moves[1] stores ahead, moves[2] stores right 
	validateMoves(clear, moves);
}

void moveSquare() {
	// Checks for walls in all three directions
	int clear[] = {isClear(-1), isClear(0) , isClear(1)}; // array storing whether or not there is a wall to the left, ahead and right respectively
	int bestMove = getBestMove(clear);
}

int main() {
	printf("Position: (%d, %d)\n" xPos, yPos);
	return 0;
}