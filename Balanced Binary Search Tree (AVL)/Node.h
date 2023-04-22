#pragma once

class Node
{
public:

	Node(int value);
	bool operator<(const int value) const;
	bool operator>(const int value) const;
	bool operator==(const int value) const;
	void Print() const;

public:
	Node * m_leftChild = nullptr;
	Node * m_rightChild = nullptr;
	int m_balancedFactor = 0;
	int m_height = 0;
	int m_value;
};