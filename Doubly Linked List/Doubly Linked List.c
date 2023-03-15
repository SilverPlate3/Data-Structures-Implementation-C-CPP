#include <stdlib.h>
#include <stdio.h>


typedef struct Node {
	struct Node* next;
	struct Node* previous;
	int value;
}Node;



/// <summary>
/// Adding a node to the end of the list. 
/// If its the first node, we will use the Head pointer 
/// Else we will use the Tail pointer for efficiency 
/// </summary>
void Append(Node** Head, Node** Tail, int number_of_nodes)
{
	//Creating the new node
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL)
	{
		printf("\nMalloc failed");
		exit(EXIT_FAILURE);
	}

	//If its the first node that will be added to the list(After Head)
	if (number_of_nodes == 1)
	{
		new_node->next = NULL;
		new_node->value = number_of_nodes;

		Node* current_node = *Head;

		current_node->next = new_node;
		new_node->previous = current_node;

		// Setting the Tail pointer to the new node
		*Tail = new_node;
	}

	// Every further node that will be appended to the linked list, will use the Tail pointer. 
	else
	{
		new_node->next = NULL;
		new_node->value = number_of_nodes;
		new_node->previous = *Tail;

		Node* current_node = *Tail;
		current_node->next = new_node;

		// Setting the Tail pointer to the new node
		*Tail = new_node;
	}

}


// -----------------------------------------------   Insert Node to list  ||   START   ----------------------------------------------------

void Adding_the_new_node(Node* current_node, Node* new_node)
{
	// Inserting the new node by modifing pointers
	new_node->next = current_node->next;
	new_node->previous = current_node;
	current_node->next->previous = new_node;
	current_node->next = new_node;
}



void Insert(Node** Head, Node** Tail, int number_of_nodes)
{
	int index, node_value;
	printf("\nIn what index do you want to insert the new Node, 0-%d: ", number_of_nodes);
	scanf_s("%d", &index, sizeof(index));

	printf("\nWhat value will the new node hold: ");
	scanf_s("%d", &node_value, sizeof(node_value));

	double check_Head_or_Tail = (double)number_of_nodes / 2.0;

	//Creating the Node to insert
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->next = NULL;
	new_node->previous = NULL;
	new_node->value = node_value;


	// If the index we want is closer to the Head then the Tail, OR right in the middle
	if (index <= check_Head_or_Tail)
	{
		//Creating a pointer
		Node* current_node = *Head;

		if (index == 0)
		{
			new_node->next = current_node;
			current_node->previous = new_node;
			*Head = current_node->previous;
		}

		else
		{
			//Iterating the list until the wanted index
			int counter = 1;
			while (counter < index)
			{
				current_node = current_node->next;
				counter++;
			}

			Adding_the_new_node(current_node, new_node);
		}
	}

	// If the index we want is closer to the Tail then the Head
	else
	{
		Node* current_node = *Tail;

		// If the user wants to insert the new node at the end
		if (index == number_of_nodes)
		{
			Append(Head, Tail, node_value);
		}

		else
		{
			//Iterating the list until the wanted index
			int counter = number_of_nodes;
			while (counter > index)
			{
				current_node = current_node->previous;
				counter--;
			}

			Adding_the_new_node(current_node, new_node);
		}
	}
}

// -----------------------------------------------   Insert Node to list  ||   END   ----------------------------------------------------



// -----------------------------------------------   Remove Node from list  ||   START   ----------------------------------------------------

void Deleting_the_removed_node(Node* current_node)
{
	// Adjusting the Previous and Next nodes pointers
	current_node->previous->next = current_node->next;
	current_node->next->previous = current_node->previous;

	// Deleting the irrelevant node.
	free(current_node);
}



void Remove(Node** Head, Node** Tail, int number_of_nodes)
{
	int index;
	printf("\nWhat index do we want to remove in range of 0 - %d: ", number_of_nodes - 1);
	scanf_s("%d", &index, sizeof(index));

	double check_Head_or_Tail = (double)number_of_nodes / 2.0;


	// If the index we want is closer to the Head then the Tail, OR right in the middle
	if (index <= check_Head_or_Tail)
	{
		//Creating a pointer
		Node* current_node = *Head;

		if (index == 0)
		{
			current_node->next->previous = NULL;
			*Head = current_node->next;
		}

		else
		{
			//Iterating the list until the wanted Index
			int counter = 0;
			while (counter < index)
			{
				current_node = current_node->next;
				counter++;
			}

			Deleting_the_removed_node(current_node);
		}
	}

	else
	{
		//Creating a pointer
		Node* current_node = *Tail;

		// If we want to remove the last node.
		if (index == number_of_nodes - 1)
		{
			current_node->previous->next = NULL;
			*Tail = current_node->previous;
			free(current_node);
		}

		else
		{
			//Iterating the list until the wanted Index
			int counter = number_of_nodes;
			while (counter > index)
			{
				current_node = current_node->previous;
				counter--;
			}

			Deleting_the_removed_node(current_node);
		}
	}
}

// -----------------------------------------------   Remove Node from list  ||   END   ----------------------------------------------------


void print_linked_list(Node* Head)
{
	Node* Node_pointer = Head;
	int counter = 0;

	while (Node_pointer != NULL)
	{
		printf("\n[%d]   Current:  %llp        Next: %llp        Previous: %llp        Value: %d", counter, Node_pointer, Node_pointer->next, Node_pointer->previous, Node_pointer->value);

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
		free(Node_pointer->previous);
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
	Head->previous = NULL;

	// Initializing the Tail
	Node* Tail = (Node*)malloc(sizeof(Node));
	Tail->next = NULL;
	Tail->value = 0;
	Tail->previous = NULL;


	//Creating the list
	for (int i = 1; i < number_of_nodes; i++)
	{
		Append(&Head, &Tail, i);
	}


	while (1)
	{
		printf("\n[+] Choose number:   1- Append      2- Remove      3- Insert      4-  Print the list       5- Print Head & Tail      6- Exit script    :     ");
		scanf_s("%d", &choise, sizeof(choise));

		switch (choise)
		{
		case 1:
			Append(&Head, &Tail, number_of_nodes);
			number_of_nodes++;
			break;

		case 2:
			Remove(&Head, &Tail, number_of_nodes);
			number_of_nodes--;
			break;

		case 3:
			Insert(&Head, &Tail, number_of_nodes);
			number_of_nodes++;
			break;

		case 4:
			print_linked_list(Head);
			break;

		case 5:
			printf("\n#HEAD#   Head address:  %llp      Next: %llp        Previous: %llp     value: %d", Head, Head->next, Head->previous, Head->value);
			printf("\n#Tail#   Tail address:  %llp      Next: %llp        Previous: %llp     value: %d\n\n\n", Tail, Tail->next, Tail->previous, Tail->value);
			break;

		case 6:
			Clear_memory(Head);
			exit(EXIT_SUCCESS);
		}
	}
}

