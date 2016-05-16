#include "simpletools.h"
#include "abdrive.h"

void bubbleSort(int arr[], int size)
{
	int y = 1;
	int x = 0;
	int sorted = 0;
 
  driveHalf();
	while(sorted == 0)
	{
		sorted = 1;
		for(x = 0; x < (size - y); x++)
		{
			if(arr[x+1] < arr[x])
			{
				int temp = arr[x+1];
				arr[x+1] = arr[x];
				arr[x] = temp;
				sorted = 0;
          blink();
			}
       if(x < (size - y - 1))
       {
         driveFull();
       }
       else
       {
         rotate180();
         driveBackToStart(x);
         rotate180();
       }               
		}
		y++;
	}
 driveToMiddle(size);
}

void driveHalf() {
  drive_goto(62, 62);
}

void driveFull() {
  drive_goto(123, 123);
}

void driveBackToStart(int n) {
  drive_goto(123*n, 123*n);
}

void driveToMiddle(int n) {
  drive_goto(123*((n-2)*0.5), 123*((n-2)*0.5));
  rotate90();
}   

void rotate90() {
  drive_goto(26, -26);
}  

void rotate180() {
  drive_goto(52, -52);
}

void blink() {
  int i;
  for(i = 0; i < 15; i++)
  {
    high(26);                                
    pause(200);                               
    low(26);                                  
    pause(200);
  }    
}  

int main() {
	int n = 5;
	int a[5] = {33, 22, 21, 18, 14};
	bubbleSort(a, n);

	return 0;
}