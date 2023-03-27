#pragma once
#include "Node.h"

class BinarySearchTree
{
public:
	BinarySearchTree(int value);
	void Insert(int value);
	bool Find(int value, const std::unique_ptr<Node>& currentNode = m_rootNode);
	void Remove(int value, std::unique_ptr<Node>& currentNode = m_rootNode);
	void TraverseTree();

private:

	void Insert(int value, const std::unique_ptr<Node>& currentNode);
	std::unique_ptr<Node>& GetCorrectChild(const std::unique_ptr<Node>& node, const int value) const;
	bool NodeHas2Children(const std::unique_ptr<Node>& node);
	std::unique_ptr<Node>& WhoMySuccessor(const std::unique_ptr<Node>& node);
	std::unique_ptr<Node>& FindSmallestNodeInRightSubTree(std::unique_ptr<Node>& node);
	void PrintInOrder(const std::unique_ptr<Node>& currentNode = m_rootNode);

private:
	static std::unique_ptr<Node> m_rootNode;
};