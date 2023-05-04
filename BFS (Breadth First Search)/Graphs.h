#pragma once
#include <vector>
#include <list>

std::vector<std::list<int>> Graph1()
{
	std::vector<std::list<int>> graph;
	graph.push_back({ 1, 3 });
	graph.push_back({ 0, 2, 4, 6, 7});
	graph.push_back({ 1, 3, 8, 9 });
	graph.push_back({ 0, 2 });
	graph.push_back({ 1, 5, 6, 7 });
	graph.push_back({ 4 });
	graph.push_back({ 1, 4, 7});
	graph.push_back({ 1, 4, 6 });
	graph.push_back({ 2 });
	graph.push_back({ 2 });

	return graph;
}