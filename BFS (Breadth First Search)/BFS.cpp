#include <iostream>

#include "Graphs.h"

class BFS
{
public:
	BFS(const std::vector<std::list<int>>& graph, int nodeToExplore)
	{
		const int numberOfNodes = graph.size();
		std::vector<bool> nodesExplored;
		nodesExplored.resize(numberOfNodes, false);
		std::list<int> nodesToExplore;

		nodesExplored[nodeToExplore] = true;
		nodesToExplore.push_back(nodeToExplore);

		while (!nodesToExplore.empty())
		{
			nodeToExplore = nodesToExplore.front();
			nodesToExplore.pop_front();

			std::cout << "\n\nCurrent node:  " << nodeToExplore << "  adjacent nodes:  ";

			for (const auto& adjacentNode : graph[nodeToExplore])
			{
				std::cout << adjacentNode << ", ";

				if (!nodesExplored[adjacentNode])
				{
					nodesExplored[adjacentNode] = true;
					nodesToExplore.push_back(adjacentNode);
				}
			}
		}
	}
};

int main()
{
	BFS bfs(Graph1(), 3);
}