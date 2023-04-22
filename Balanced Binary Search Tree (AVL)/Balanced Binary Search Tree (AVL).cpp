#include "Balanced Binary Search Tree (AVL).h"
#include <iostream>
#include <string>


AvlTree::AvlTree(int value)
{
	m_rootNode = new Node(value);
}

void AvlTree::Insert(int value)
{
	if (Find(value))
	{
		std::cout << "Duplicate value! can't insert: " << value << std::endl;
		return;
	}

	m_rootNode = Insert(value, m_rootNode);
}

Node* AvlTree::Insert(int value, Node* currentNode)
{
	if (currentNode == nullptr)
	{
		return new Node(value);
	}

	if (*currentNode < value)
	{
		currentNode->m_rightChild = Insert(value, currentNode->m_rightChild);
	}
	else
	{
		currentNode->m_leftChild = Insert(value, currentNode->m_leftChild);
	}

	SetHeightAndBalancedFactorToCurrentNode(currentNode);
	return Rebalance(currentNode);
}

void AvlTree::Remove(int value)
{
	if (!Find(value))
	{
		std::cout << "Value isn't in the tree" << std::endl;
		return;
	}

	m_rootNode = Remove(value, m_rootNode);
}

Node* AvlTree::Remove(int value, Node* currentNode)
{
	if (currentNode == nullptr)
	{
		return nullptr;
	}

	if (*currentNode < value)
	{
		currentNode->m_rightChild = Remove(value, currentNode->m_rightChild);
	}
	else if (*currentNode > value)
	{
		currentNode->m_leftChild = Remove(value, currentNode->m_leftChild);
	}
	else
	{
		if (currentNode->m_leftChild == nullptr)
		{
			auto rightChild = currentNode->m_rightChild;
			delete currentNode;
			return rightChild;
		}

		if (currentNode->m_rightChild == nullptr)
		{
			auto leftChild = currentNode->m_leftChild;
			delete currentNode;
			return leftChild;
		}

		auto successorValue = FindSmallestNodeInRightSubTree(currentNode->m_rightChild)->m_value;
		currentNode->m_value = successorValue;
		currentNode->m_rightChild = Remove(successorValue, currentNode->m_rightChild);
	}

	SetHeightAndBalancedFactorToCurrentNode(currentNode);
	return Rebalance(currentNode);
}

bool AvlTree::Find(int value, Node* currentNode)
{
	if (currentNode == nullptr)
	{
		return false;
	}

	if (*currentNode == value)
	{
		return true;
	}
	auto nextNode = GetCorrectChild(currentNode, value);

	return Find(value, nextNode);
}

void AvlTree::SetHeightAndBalancedFactorToCurrentNode(Node* currentNode)
{
	auto rightSubtreeHeight = -1, leftSubtreeHeight = -1;
	if (currentNode->m_rightChild)
	{
		rightSubtreeHeight = currentNode->m_rightChild->m_height;
	}
	if (currentNode->m_leftChild)
	{
		leftSubtreeHeight = currentNode->m_leftChild->m_height;
	}

	currentNode->m_height = std::max(rightSubtreeHeight, leftSubtreeHeight) + 1;
	currentNode->m_balancedFactor = rightSubtreeHeight - leftSubtreeHeight;
}

Node* AvlTree::Rebalance(Node* currentNode)
{
	if (currentNode->m_balancedFactor > 2 || currentNode->m_balancedFactor < -2)
	{
		std::cout << "Error in the implementation! The Balanced Factor can't be outside the range of -2<X<2" << std::endl;
		exit(1);
	}

	if (currentNode->m_balancedFactor == -2)
	{
		return LeftSubtreeTooHigh(currentNode);
	}

	if (currentNode->m_balancedFactor == 2)
	{
		return RightSubtreeTooHigh(currentNode);
	}

	return currentNode;
}

Node* AvlTree::LeftSubtreeTooHigh(Node* currentNode)
{
	if (currentNode->m_leftChild->m_balancedFactor <= 0)
	{
		return LeftLeft(currentNode);
	}

	return LeftRight(currentNode);
}

Node* AvlTree::RightSubtreeTooHigh(Node* currentNode)
{
	if (currentNode->m_rightChild->m_balancedFactor >= 0)
	{
		return RightRight(currentNode);
	}

	return RightLeft(currentNode);
}

Node* AvlTree::LeftLeft(Node* currentNode)
{
	return RightRotation(currentNode);
}

Node* AvlTree::LeftRight(Node* currentNode)
{
	currentNode->m_leftChild = LeftRotation(currentNode->m_leftChild);
	return LeftLeft(currentNode);
}

Node* AvlTree::RightRight(Node* currentNode)
{
	return LeftRotation(currentNode);
}

Node* AvlTree::RightLeft(Node* currentNode)
{
	currentNode->m_rightChild = RightRotation(currentNode->m_rightChild);
	return LeftRotation(currentNode);
}

Node* AvlTree::RightRotation(Node* currentNode)
{
	Node* currentNodeLeftChild = currentNode->m_leftChild;
	currentNode->m_leftChild = nullptr;
	currentNode->m_leftChild = currentNodeLeftChild->m_rightChild;
	currentNodeLeftChild->m_rightChild = nullptr;
	currentNodeLeftChild->m_rightChild = currentNode;

	SetHeightAndBalancedFactorToCurrentNode(currentNode);
	SetHeightAndBalancedFactorToCurrentNode(currentNodeLeftChild);

	return currentNodeLeftChild;
}

Node* AvlTree::LeftRotation(Node* currentNode)
{
	Node* currentNodeRightChild = currentNode->m_rightChild;
	currentNode->m_rightChild = nullptr;
	currentNode->m_rightChild = currentNodeRightChild->m_leftChild;
	currentNodeRightChild->m_leftChild = currentNode;

	SetHeightAndBalancedFactorToCurrentNode(currentNode);
	SetHeightAndBalancedFactorToCurrentNode(currentNodeRightChild);

	return currentNodeRightChild;
}

// When removing a node that has two child nodes. We need to swap its value with the value of the smallest value in the right subtree.
Node* AvlTree::FindSmallestNodeInRightSubTree(Node* node)
{
	return node->m_leftChild ? FindSmallestNodeInRightSubTree(node->m_leftChild) : node;
}


// Print the tree nodes from smallest value to largest
void AvlTree::TraverseTree()
{
	PrintInOrder();
	std::cout << "\n" << std::endl;
}

void AvlTree::PrintInOrder(const Node* currentNode)
{
	if (currentNode == nullptr)
	{
		return;
	}

	PrintInOrder(currentNode->m_leftChild);
	currentNode->Print();
	PrintInOrder(currentNode->m_rightChild);
}

void AvlTree::PrintChildren(int value, const Node* currentNode)
{
	if (currentNode == nullptr)
	{
		std::cout << "Value not in tree " << std::endl;
	}
	else if (*currentNode == value)
	{
		PrintChildren(currentNode);
	}
	else
	{
		auto nextNode = GetCorrectChild(currentNode, value);
		PrintChildren(value, nextNode);
	}
}

void AvlTree::PrintChildren(const Node* currentNode)
{
	const auto leftChildValue = currentNode->m_leftChild ? std::to_string(currentNode->m_leftChild->m_value) : "NULL";
	const auto rightChildValue = currentNode->m_rightChild ? std::to_string(currentNode->m_rightChild->m_value) : "NULL";

	std::cout << "    " << currentNode->m_value << "    " << std::endl;
	std::cout << "   /  \\ " << std::endl;
	std::cout << leftChildValue << "      " << rightChildValue <<  std::endl;
}

Node* AvlTree::GetCorrectChild(const Node* node, const int value) const
{
	return (*node < value) ? node->m_rightChild : node->m_leftChild;
}

Node* AvlTree::m_rootNode = nullptr;


int main()
{
	std::cout << "Select Root Value: ";
	int initialValue;
	std::cin >> initialValue;
	AvlTree avl(initialValue);

	while (true)
	{
		std::cout << "\nSelect an option   1- Insert    2- Remove    3- Contains     4- Traverse    5- Print Children:";
		int choice;
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			std::cout << "\nValue to insert: ";
			int valueToAdd;
			std::cin >> valueToAdd;
			avl.Insert(valueToAdd);
			break;

		case 2:
			std::cout << "\nValue to Remove: ";
			int valueToRemove;
			std::cin >> valueToRemove;
			avl.Remove(valueToRemove);
			break;

		case 3:
			std::cout << "\nValue to Find: ";
			int valueToFind;
			std::cin >> valueToFind;
			std::cout << "The AVL contains " << valueToFind << " :" << std::boolalpha << avl.Find(valueToFind) << std::endl;
			break;

		case 4:
			avl.TraverseTree();
			break;

		case 5:
			std::cout << "\nParent node value: ";
			int parentNodeValue;
			std::cin >> parentNodeValue;
			avl.PrintChildren(parentNodeValue);
			break;
		}
	}
}