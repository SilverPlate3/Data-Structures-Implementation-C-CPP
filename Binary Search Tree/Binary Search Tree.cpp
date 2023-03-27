#include "Binary Search Tree.h"
#include <iostream>

BinarySearchTree::BinarySearchTree(int value)
{
	m_rootNode = std::make_unique<Node>(value);
}

void BinarySearchTree::TraverseTree()
{
	PrintInOrder();
}

void BinarySearchTree::PrintInOrder(const std::unique_ptr<Node>& currentNode)
{
	if (currentNode == nullptr)
	{
		return;
	}

	PrintInOrder(currentNode->m_leftChild);
	currentNode->Print();
	PrintInOrder(currentNode->m_rightChild);
}

void BinarySearchTree::Insert(int value)
{
	if (m_rootNode == nullptr)
	{
		m_rootNode = std::make_unique<Node>(value);
		return;
	}

	Insert(value, std::make_unique<Node>(value));
}

void BinarySearchTree::Insert(int value, const std::unique_ptr<Node>& currentNode)
{
	if (*currentNode == value)
	{
		std::cout << "Duplicate value! can't insert: " << value << std::endl;
		return;
	}

	auto& nextNode = GetCorrectChild(currentNode, value);
	if (nextNode == nullptr)
	{
		auto newNode = std::make_unique<Node>(value);
		nextNode = std::move(newNode);
		return;
	}

	Insert(value, nextNode);
}


std::unique_ptr<Node>& BinarySearchTree::GetCorrectChild(const std::unique_ptr<Node>& node, const int value) const
{
	return (*node < value) ? node->m_rightChild : node->m_leftChild;
}


bool BinarySearchTree::Find(int value, const std::unique_ptr<Node>& currentNode)
{
	if (currentNode == nullptr)
	{
		return false;
	}

	if (*currentNode == value)
	{
		return true;
	}
	auto& nextNode = GetCorrectChild(currentNode, value);

	return Find(value, nextNode);
}

void BinarySearchTree::Remove(int value, std::unique_ptr<Node>& currentNode)
{
	if(currentNode == nullptr)
	{
		std::cout << "The value " << value << " isn't in the tree" << std::endl;
		return;
	}
	if (*currentNode == value)
	{
		auto& successor = WhoMySuccessor(currentNode);
		if (NodeHas2Children(currentNode))
		{
			*currentNode = *successor;
			successor = std::move(successor->m_rightChild);
		}
		else
		{
			currentNode = std::move(successor);
		}
	}
	else
	{
		auto& nextNode = GetCorrectChild(currentNode, value);
		Remove(value, nextNode);
	}
}

std::unique_ptr<Node>& BinarySearchTree::WhoMySuccessor(const std::unique_ptr<Node>& node)
{
	if (node->m_leftChild == nullptr)
	{
		return node->m_rightChild;
	}

	if (node->m_rightChild == nullptr)
	{
		return node->m_leftChild;
	}

	return FindSmallestNodeInRightSubTree(node->m_rightChild);
}

bool BinarySearchTree::NodeHas2Children(const std::unique_ptr<Node>& node)
{
	return (node->m_rightChild && node->m_leftChild);
}

std::unique_ptr<Node>& BinarySearchTree::FindSmallestNodeInRightSubTree(std::unique_ptr<Node>& node)
{
	return node->m_leftChild ? FindSmallestNodeInRightSubTree(node->m_leftChild) : node;
}


std::unique_ptr<Node> BinarySearchTree::m_rootNode = nullptr;



int main()
{
	std::cout << "Select Root Value: ";
	int initialValue;
	std::cin >> initialValue;
	BinarySearchTree BinarySearchTree(initialValue);

	while (true)
	{
		std::cout << "\nSelect an option   1- Insert    2- Remove    3- Contains     4- Traverse :";
		int choice;
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			std::cout << "\nValue to insert: ";
			int valueToAdd;
			std::cin >> valueToAdd;
			BinarySearchTree.Insert(valueToAdd);
			break;

		case 2:
			std::cout << "\nValue to Remove: ";
			int valueToRemove;
			std::cin >> valueToRemove;
			BinarySearchTree.Remove(valueToRemove);
			break;

		case 3:
			std::cout << "\nValue to Find: ";
			int valueToFind;
			std::cin >> valueToFind;
			std::cout << "The BST contains " << valueToFind << " :" << std::boolalpha << BinarySearchTree.Find(valueToFind) << std::endl;
			break;

		case 4:
			BinarySearchTree.TraverseTree();
			break;
		}
	}
}