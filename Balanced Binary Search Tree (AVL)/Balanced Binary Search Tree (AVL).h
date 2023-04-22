#pragma once
#include "Node.h"


class AvlTree
{
public:
	AvlTree(int value);
	void Insert(int value);
	bool Find(int value, Node* currentNode = m_rootNode);
	void Remove(int value);
	void TraverseTree();
	void PrintChildren(int value, const Node* currentNode = m_rootNode);
private:
	Node* Insert(int value, Node* currentNode);
	void SetHeightAndBalancedFactorToCurrentNode(Node* currentNode);
	Node* Rebalance(Node* currentNode);
	Node* LeftSubtreeTooHigh(Node* currentNode);
	Node* RightSubtreeTooHigh(Node* currentNode);
	Node* LeftLeft(Node* currentNode);
	Node* LeftRight(Node* currentNode);
	Node* RightRight(Node* currentNode);
	Node* RightLeft(Node* currentNode);
	Node* RightRotation(Node* currentNode);
	Node* LeftRotation(Node* currentNode);
	Node* Remove(int value, Node* currentNode);
	Node* GetCorrectChild(const Node* node, const int value) const;
	Node* FindSmallestNodeInRightSubTree(Node* node);
	void PrintInOrder(const Node* currentNode = m_rootNode);
	void PrintChildren(const Node* currentNode);

private:
	static Node* m_rootNode;
};