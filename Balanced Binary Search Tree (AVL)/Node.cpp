#include "Node.h"
#include <iostream>

Node::Node(int value) :
	m_leftChild(nullptr), m_rightChild(nullptr), m_value(value) {}


bool Node::operator<(const int value) const
{
	return m_value < value;
}

bool Node::operator>(const int value) const
{
	return m_value > value;
}

bool Node::operator==(const int value) const
{
	return m_value == value;
}

void Node::Print() const
{
	std::cout << m_value << ", ";
}