#include "Graphs.h"
#include <iostream>

template<typename T>
class BFS
{
public:
	BFS()
	{
		auto root = IntegersGraph();
		m_nodesToExplore.emplace_back(std::move(root));
		Explore();
	}

private:

	void Explore()
	{
		while (m_nextToExplore != m_nodesToExplore.size())
		{
			std::cout << "\nCurrent value: " << m_nodesToExplore.at(m_nextToExplore)->value << " adjacent nodes: ";

			const auto currentNodeToExplore = m_nodesToExplore.at(m_nextToExplore);
			currentNodeToExplore->isExplored = true;

			for (auto& node : currentNodeToExplore->adjacentNodes)
			{
				std::cout << node->value << ", ";
				if(!node->isExplored)
				{
					node->isExplored = true;
					m_nodesToExplore.emplace_back(node);
				}
			}

			m_nextToExplore++;
		}
	}

private:
	std::vector<NodeSPtr<T>> m_nodesToExplore;
	int m_nextToExplore = 0;
};

int main()
{
	BFS<int> bfs;
}
