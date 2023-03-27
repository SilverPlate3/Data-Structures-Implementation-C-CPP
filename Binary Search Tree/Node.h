#pragma once
#include <memory>


class Node
{
public:

	Node(int value);
	bool operator<(const int value) const;
	bool operator==(const int value) const;
	void operator=(const int value);
	void operator=(const Node& other);
	void Print();

public:
	std::unique_ptr<Node> m_leftChild;
	std::unique_ptr<Node> m_rightChild;

private:
	int m_value;
};