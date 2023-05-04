#pragma once
#include <vector>
#include <memory>


template<typename T>
struct Node
{
	T value;
	bool isExplored = false;
	std::vector<std::shared_ptr<Node>> adjacentNodes;
};

template<typename T>
using NodeSPtr = std::shared_ptr<Node<T>>;