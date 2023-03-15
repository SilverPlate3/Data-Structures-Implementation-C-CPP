#include <stdlib.h>
#include <stdio.h>


typedef struct Node {
	struct Node* next;
	int value;
}Node;



void Push(Node** Head)
{
	// Creating a new Node
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL)
	{
		printf("\nMalloc failed");
		exit(EXIT_FAILURE);
	}

	// Giving the new node a value
	int value;
	printf("\nValue of node: ");
	scanf_s("%d", &value, sizeof(value));

	// Inserting the node to the Head of the list
	new_node->value = value;
	new_node->next = *Head;
	*Head = new_node;
}



Node* Pop(Node** Head)
{
	// Checking if top of the list is NULL
	if (*Head == NULL)
		return NULL;

	// moving the Head pointer to the next in the list, AND returning the previos Head.
	Node* current_node = *Head;
	*Head = current_node->next;
	return current_node;
}




void main(int argc, char** argv)
{
	int choise;
	printf("####  Creating the Linked List  ####");

	// Initializing the Head. The Head will be moved but this object will always represent the bottom of the list. 
	Node* Head = NULL;

	Node* holder;

	while (1)
	{
		printf("\nSelect an option        1- Push        2- Pop       3- Peak      4 - Clear stack and exit : ");
		scanf_s("%d", &choise, sizeof(choise));

		switch (choise)
		{
			// Push
		case 1:
			Push(&Head);
			break;

			// Pop
		case 2:
			holder = Pop(&Head);
			if (holder != NULL)
				printf("\nPoped - %u", holder->value);
			else
				printf("\nCouldn't pop, stack is empty!");
			break;

			// Peak
		case 3:
			holder = Pop(&Head);
			if (holder != NULL)
			{
				printf("\nTop value - %u", holder->value);

				// Inserting the node back to the list, and making it the Head.
				holder->next = Head;
				Head = holder;
			}
			else
				printf("\nStack is empty!");

			break;

			// Clear stack
		case 4:

			// Iterating through the list and freeing the nodes as they were dynamiclly allocated.
			// Until we meet the bottom value which is NULL and was created localy.
			while (1)
			{
				holder = Pop(&Head);
				if (holder != NULL)
					free(holder);

				else
					break;
			}
			printf("\nStack is cleared!  Exiting script.....");
			exit(EXIT_SUCCESS);
		}

	}


}

