#include <iostream>
#include "../BFS (Breadth First Search)/Graphs.h"

class DFS
{
public:
	DFS(const std::vector<std::list<int>>& graph)
		:m_graph(graph), m_numberOfNodes(m_graph.size())
	{
		m_nodesExplored.resize(m_numberOfNodes, false);
	}

	void Explore(const int nodeToExplore)
	{
		m_nodesExplored[nodeToExplore] = true;
		for (const auto& adjacentNode : m_graph[nodeToExplore])
		{
			if(!m_nodesExplored[adjacentNode])
			{
				std::cout << nodeToExplore << " -> " << adjacentNode << std::endl;
				Explore(adjacentNode);

				std::cout << nodeToExplore << std::endl;
			}
		}

		std::cout << "Can't continue to explore: " << nodeToExplore << " Going back to: ";
	}

private:
	const std::vector<std::list<int>> m_graph;
	int m_numberOfNodes;
	std::vector<bool> m_nodesExplored;
};

int main()
{
	DFS dfs(Graph1());
	dfs.Explore(3);
	std::cout << "Done exploring!" << std::endl;
}




