#pragma once

#include "Node.h"

NodeSPtr<int> IntegersGraph()
{
	auto node1 = std::make_shared<Node<int>>(); node1->value = 1;
	auto node2 = std::make_shared<Node<int>>(); node2->value = 2;
	auto node3 = std::make_shared<Node<int>>(); node3->value = 3;
	auto node4 = std::make_shared<Node<int>>(); node4->value = 4;
	auto node5 = std::make_shared<Node<int>>(); node5->value = 5;
	auto node6 = std::make_shared<Node<int>>(); node6->value = 6;
	auto node7 = std::make_shared<Node<int>>(); node7->value = 7;
	auto node8 = std::make_shared<Node<int>>(); node8->value = 8;
	auto node9 = std::make_shared<Node<int>>(); node9->value = 9;
	auto node10 = std::make_shared<Node<int>>(); node10->value = 10;

	node1->adjacentNodes.push_back(node2);
	node1->adjacentNodes.push_back(node4);

	node2->adjacentNodes.push_back(node1);
	node2->adjacentNodes.push_back(node3);
	node2->adjacentNodes.push_back(node5);
	node2->adjacentNodes.push_back(node7);
	node2->adjacentNodes.push_back(node8);

	node3->adjacentNodes.push_back(node2);
	node3->adjacentNodes.push_back(node4);
	node3->adjacentNodes.push_back(node9);
	node3->adjacentNodes.push_back(node10);

	node4->adjacentNodes.push_back(node1);
	node4->adjacentNodes.push_back(node3);

	node5->adjacentNodes.push_back(node2);
	node5->adjacentNodes.push_back(node6);
	node5->adjacentNodes.push_back(node7);
	node5->adjacentNodes.push_back(node8);

	node6->adjacentNodes.push_back(node5);

	node7->adjacentNodes.push_back(node2);
	node7->adjacentNodes.push_back(node5);
	node7->adjacentNodes.push_back(node8);

	node8->adjacentNodes.push_back(node2);
	node8->adjacentNodes.push_back(node5);
	node8->adjacentNodes.push_back(node7);

	node9->adjacentNodes.push_back(node3);

	node10->adjacentNodes.push_back(node3);

	return node7;
}

