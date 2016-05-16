#include "simpletools.h"

void displayArray(int arr[], int n)
{
	int i;
	for(i = 0; i < n; i++)
	{
		print("%d\t", arr[i]);
	}
	print("\n");
}

int getArraySize()
{
	print("Enter number of elements\n");
	int n;
	scanf("%d", &n);
	return n;
}

void getElements(int arr[], int n)
{
	print("Enter %d numbers\n", n);
	int i;
	for (i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}
	print("\n");
}

void bubbleSort(int arr[], int size)
{
	int y = 1;
	int x = 0;
	int sorted = 0;
 
	while(sorted == 0)
	{
		sorted = 1;
		for(x = 0; x < (size - y); x++)
		{
        displayArray(arr, size);
			if(arr[x+1] < arr[x])
			{
				int temp = arr[x+1];
				arr[x+1] = arr[x];
				arr[x] = temp;
				sorted = 0;
			}              
		}
		y++;
	}
}

int main() {
	int n = getArraySize();
	int a[n];
	getElements(a, n);
	bubbleSort(a, n);
	displayArray(a, n);

	return 0;
}