#pragma once
#include <unordered_map>
#include <vector>

class UnionFind
{
public:

	UnionFind(int numberOfElements);

	int Find(int element);

	void Union(int elementA, int elementB);

	int GroupSize(int element);

	int NumberOfGroups();

	void PrintUnionFind();

private:

	void PathCompression(int rootElement, int element);

private:
	int m_numberOfElements;
	int m_numberOfGroups;
	std::vector<int> m_whoIsMyParent;
	std::unordered_map<int, int> m_groupSizes;
};
