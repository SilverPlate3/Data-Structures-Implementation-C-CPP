#include <stdlib.h>
#include <stdio.h>

#define QUEUE_MAX_LENGTH 10

int first_time = true;

void Enqueue(int queue[], int* queue_content_counter)
{
	int value;
	printf("\nNew object value: ");
	scanf_s("%d", &value, sizeof(value));

	if (*queue_content_counter < (QUEUE_MAX_LENGTH - 1))
	{
		queue[*queue_content_counter] = value;
		(*queue_content_counter)++;
	}
	else
	{
		if (!first_time)
		{
			for (int i = 0; i <= (QUEUE_MAX_LENGTH - 1); i++)
			{
				queue[i] = queue[i + 1];
			}
			queue[*queue_content_counter] = value;
		}
		else
		{
			first_time = false;
			queue[*queue_content_counter] = value;
		}

	}
}

int Dequeue(int queue[], int* queue_content_counter)
{
	if ((*queue_content_counter) == 0)
	{
		printf("\nList is empty, can't Dequeue");
		return 1;
	}

	int dequeued_value = queue[0];
	for (int i = 0; i < *queue_content_counter; i++)
	{
		queue[i] = queue[i + 1];
	}
	(*queue_content_counter)--;
	first_time = true;
	return dequeued_value;
}

void PrintQueue(int queue[], int* queue_content_counter)
{
	printf("\n Queue content {Head} <-- {Tail}: ");
	if (first_time)
	{
		for (int i = 0; i < *queue_content_counter; i++)
		{
			printf("%d, ", queue[i]);
		}
	}
	else
	{
		for (int i = 0; i <= *queue_content_counter; i++)
		{
			printf("%d, ", queue[i]);
		}
	}

}


void main(int argc, char** argv)
{
	int queue[QUEUE_MAX_LENGTH] = { 0 };
	int queue_content_counter = 0;

	int choise;
	while (true) {
		printf("\nSelect operation     1- Enqueue       2- Dequeue       3- Print Queue      4-  Exit    : ");
		scanf_s("%d", &choise, sizeof(choise));

		switch (choise)
		{
		case 1:
		{
			Enqueue(queue, &queue_content_counter);
			break;
		}
		case 2:
		{
			Dequeue(queue, &queue_content_counter);
			break;
		}
		case 3:
		{
			PrintQueue(queue, &queue_content_counter);
			break;
		}
		case 4:
			exit(EXIT_SUCCESS);
		}
	}
}

