#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
	struct Node* next;
	int value ;
}Node;

void Append(Node** Head, int i)
{
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL)
	{
		printf("\nMalloc failed");
		exit(EXIT_FAILURE);
	}

	new_node->next = NULL;
	new_node->value = i;

	Node* current_node = *Head;

	while (current_node->next != NULL)
	{
		current_node = current_node->next;
	}

	current_node->next = new_node;
}

void Insert(Node** Head, int number_of_nodes)
{
	int index, node_value;
	printf("\nIn what index do you want to insert the new Node  0 - %d: ", number_of_nodes);
	scanf_s("%d", &index, sizeof(index));

	printf("\nWhat value will the new node hold: ");
	scanf_s("%d", &node_value, sizeof(node_value));

	//Creating the Node to insert
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->next = NULL;
	new_node->value = node_value;

	// Node pointer
	Node* current_node = *Head;

	// If we want to insert the node as the new Head.
	if (index == 0)
	{
		new_node->next = current_node;
		*Head = new_node;
	}

	else
	{
		// Iterate through the list until we find the needed index
		int counter = 1;
		while (counter < index)
		{
			current_node = current_node->next;
			counter++;
		}

		// Inserting the new node by modifing the some pointers
		new_node->next = current_node->next;
		current_node->next = new_node;
	}
}

void Remove(Node** Head, int number_of_nodes)
{
	int index;
	printf("\nWhat index do we want to remove  0 - %d: ", number_of_nodes - 1);
	scanf_s("%d", &index, sizeof(index));

	//Creating a pointer
	Node* current_node = *Head;

	// temp Node pointer
	Node* temp_node_pointer = *Head;

	if (index == 0)
	{
		*Head = current_node->next;
		free(current_node);
	}

	else
	{
		int counter = 1;
		while (counter < index)
		{
			current_node = current_node->next;
			counter++;
		}
		temp_node_pointer = current_node->next;
		current_node->next = temp_node_pointer->next;
		free(temp_node_pointer);
	}
}

void print_linked_list(Node* Head)
{
	Node* Node_pointer = Head;
	int counter = 0;

	while (Node_pointer != NULL)
	{
		printf("\n[%d]   Current:  %llp        Next: %llp      Value: %d", counter, Node_pointer, Node_pointer->next, Node_pointer->value);

		Node_pointer = Node_pointer->next;
		counter++;
	}
	printf("\n\n");
}

void Clear_memory(Node* Head)
{
	Node* Node_pointer = Head->next;

	while (Node_pointer->next != NULL)
	{
		free(Head);
		Head = Node_pointer;
		Node_pointer = Node_pointer->next;
	}
	free(Node_pointer);
}

void main(int argc, char** argv)
{
	int number_of_nodes = 0;
	int choise;
	printf("####  Creating the Linked List  ####");
	printf("\nHow many nodes should we start with: ");
	scanf_s("%d", &number_of_nodes, sizeof(number_of_nodes));


	// Initializing the Head
	Node* Head = (Node*)malloc(sizeof(Node));
	Head->next = NULL;
	Head->value = 0;


	//Creating the list
	for (int i = 1; i < number_of_nodes; i++)
	{
		Append(&Head, i);
	}


	while (1)
	{
		printf("\n[+] Choose number:   1- Append      2- Remove      3- Insert      4-  Print the list     5- Exit script    :     ");
		scanf_s("%d", &choise, sizeof(choise));

		switch (choise)
		{
		case 1:
			Append(&Head, number_of_nodes);
			number_of_nodes++;
			break;

		case 2:
			Remove(&Head, number_of_nodes);
			number_of_nodes--;
			break;

		case 3:
			Insert(&Head, number_of_nodes);
			number_of_nodes++;
			break;

		case 4:
			print_linked_list(Head);
			break;


		case 5:
			Clear_memory(Head);
			exit(EXIT_SUCCESS);
		}
	}
}

