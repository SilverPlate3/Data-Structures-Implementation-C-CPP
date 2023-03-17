#pragma once
#include <vector>
#include <unordered_map>
#include <set>


class BinaryHeap
{
public:

	BinaryHeap(int initialValue);
	void Peek();
	void Poll();
	void Size();
	void Add(int value);
	void RemoveValue(int value);
	void RemoveIndex(int index);
	void PrintHeap();

private:

	bool IsContainsValue(int value);
	int LastIndex();
	void BubbleUp(int index);
	void BubbleDown(int index);
	void SwapNodes(int indexA, int indexB);
	void SwapNodesMap(int indexA, int valueAtIndexA, int indexB, int valueAtIndexB);
	bool IsNodeSmaller(int index1, int index2);
	void MapRemove(int value, int index);
	void MapAdd(int value, int index);
	int MapGetIndexOf(int value);

private:
	std::vector<int> m_heap;
	std::unordered_map<int, std::set<int>> m_map;
};
