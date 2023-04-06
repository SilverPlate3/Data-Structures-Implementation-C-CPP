#include <stdlib.h>
#include <stdio.h>

#define TRUE 1

int GetUserInput(const char * message)
{
	printf("\n%s", message);
	int input;
	if(scanf_s("%d", &input, sizeof(input)) <= 0)
	{
		exit(1);
	}

	return input;
}

void InitializeArrays(int* originalArray, int* prefixSumArray, const int originalArraySize)
{
	printf("\nStarting to initialize the array with %d values", originalArraySize);
	int j = 1;
	for(int i = 0; i < originalArraySize; i++, j++)
	{
		int number = GetUserInput("Set value: ");
		originalArray[i] = number;
		prefixSumArray[j] = prefixSumArray[j - 1] + originalArray[i];
	}
}

void PrintArray(int* array, int arraySize)
{
	printf("\n");
	for(int i = 0; i < arraySize; i++)
	{
		printf("%d, ", array[i]);
	}
}

int RangeSumQuery(int startIndex, int endIndex, int* prefixSumArray)
{
	return prefixSumArray[endIndex] - prefixSumArray[startIndex];
}

void main()
{
	printf("Array size: ");
	int arraySize;
	scanf_s("%d", &arraySize, sizeof(arraySize));

	int* originalArray = (int*)calloc(arraySize, sizeof(int));
	int* prefixSumArray = (int*)calloc(arraySize + 1, sizeof(int));

	InitializeArrays(originalArray, prefixSumArray, arraySize);

	while (TRUE) 
	{
		int choice = GetUserInput("Select operation     1- Range Sum Query (none inclusive)        2- Range Sum Query (inclusive)        3- Print arrays    : ");

		switch (choice)
		{
		case 1:
		case 2:
			int startIndex = GetUserInput("From index: ");
			int endIndex = GetUserInput("to index: ");
			while (endIndex >= arraySize)
			{
				endIndex = GetUserInput("to index: ");
			}

			int sum = (choice == 1) ? RangeSumQuery(startIndex, endIndex, prefixSumArray) : RangeSumQuery(startIndex, endIndex + 1, prefixSumArray);
			printf("\nSum of arr[%d] to arr[%d]  =  %d", startIndex, endIndex, sum);
			break;

		case 3:
			printf("\nArrays: ");
			PrintArray(originalArray, arraySize);
			PrintArray(prefixSumArray, arraySize + 1);
			break;
		}
	}
}
