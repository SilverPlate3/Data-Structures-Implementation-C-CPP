#include "Binary Heap.h"
#include <iostream>


BinaryHeap::BinaryHeap(int initialValue)
{
	Add(initialValue);
}

void BinaryHeap::Add(int value)
{
	m_heap.emplace_back(value);
	MapAdd(value, LastIndex());
	BubbleUp(LastIndex());
}

void BinaryHeap::Peek()
{
	if (m_heap.empty())
	{
		std::cout << "Heap is empty!" << std::endl;
	}
	else
	{
		std::cout << "Heap Root value: " << m_heap.at(0) << std::endl;
	}
}

void BinaryHeap::Poll()
{
	RemoveIndex(0);
}

void BinaryHeap::Size()
{
	std::cout << "Heap size: " << m_heap.size() << std::endl;
}

void BinaryHeap::RemoveValue(int value)
{
	if (!IsContainsValue(value))
	{
		std::cout << "The heap doesn't contain the value: " << value << std::endl;
		return;
	}

	auto index = MapGetIndexOf(value);
	RemoveIndex(index);
}

void BinaryHeap::RemoveIndex(int index)
{
	if (index > LastIndex())
	{
		std::cout << "The heap doesn't contain the index: " << index << std::endl;
		return;
	}

	auto valueToRemove = m_heap.at(index);
	SwapNodes(index, LastIndex());

	auto lastIndexBeforeRemoval = LastIndex();
	m_heap.pop_back();
	MapRemove(valueToRemove, lastIndexBeforeRemoval);

	if (index == lastIndexBeforeRemoval)
	{
		return;
	}

	auto value = m_heap.at(index);
	BubbleDown(index);
	if (m_heap.at(index) == value)
	{
		BubbleUp(index);
	}
}

void BinaryHeap::PrintHeap()
{
	if (m_heap.size() > 15)
	{
		std::cout << "Tree more then 4 layers. To big to print";
		return;
	}

	std::cout << "\n============= HEAP ============\n" << std::endl;

	int n = m_heap.size();
	int row = 0;
	int rowStart = 0;

	while (rowStart < n)
	{
		std::cout << std::string((1 << (n - row - 1)) - 1, ' ');
		int rowEnd = std::min(rowStart + (1 << row), n);
		for (int i = rowStart; i < rowEnd; i++)
		{
			std::cout << m_heap[i] << std::string((1 << (n - row)) - 1, ' ');
		}
		std::cout << std::endl;
		row++;
		rowStart = rowEnd;
	}
}

void BinaryHeap::BubbleUp(int index)
{
	int parent = (index - 1) / 2;
	const int ROOT_NODE_INDEX = 0;
	while (index > ROOT_NODE_INDEX && IsNodeSmaller(index, parent))
	{
		SwapNodes(parent, index);
		index = parent;
		parent = (index - 1) / 2;
	}
}

void BinaryHeap::BubbleDown(int index)
{
	while (true)
	{
		int leftChildIndex = 2 * index + 1;
		int rightChildIndex = 2 * index + 2;
		int smallestChild = ((rightChildIndex < LastIndex()) && IsNodeSmaller(rightChildIndex, leftChildIndex)) ? rightChildIndex : leftChildIndex;
		if (leftChildIndex > LastIndex() || IsNodeSmaller(index, smallestChild))
		{
			break;
		}

		SwapNodes(smallestChild, index);
		index = smallestChild;
	}
}

void BinaryHeap::SwapNodes(int indexA, int indexB)
{
	auto valueAtIndexA = m_heap.at(indexA);
	auto valueAtIndexB = m_heap.at(indexB);

	m_heap.at(indexA) = valueAtIndexB;
	m_heap.at(indexB) = valueAtIndexA;

	SwapNodesMap(indexA, valueAtIndexA, indexB, valueAtIndexB);
}

void BinaryHeap::SwapNodesMap(int indexA, int valueAtIndexA, int indexB, int valueAtIndexB)
{
	auto& mapValueA = m_map.at(valueAtIndexA);
	auto& mapValueB = m_map.at(valueAtIndexB);

	mapValueA.erase(indexA);
	mapValueB.erase(indexB);

	mapValueA.insert(indexB);
	mapValueB.insert(indexA);
}

void BinaryHeap::MapRemove(int value, int index)
{
	auto mapIterator = m_map.find(value);
	auto setIterator = mapIterator->second.find(index);
	mapIterator->second.erase(setIterator);
	if (mapIterator->second.empty())
	{
		m_map.erase(mapIterator);
	}
}

void BinaryHeap::MapAdd(int value, int index)
{
	auto mapIterator = m_map.find(value);
	if (mapIterator == m_map.end())
	{
		m_map[value] = std::set<int>{ index };
	}
	else
	{
		mapIterator->second.emplace(index);
	}
}

int BinaryHeap::MapGetIndexOf(int value)
{
	return *m_map.at(value).begin();
}


bool BinaryHeap::IsNodeSmaller(int index1, int index2)
{
	return (m_heap.at(index1) < m_heap.at(index2)) ? true : false;
}

bool BinaryHeap::IsContainsValue(int value)
{
	return m_map.count(value);
}

int BinaryHeap::LastIndex()
{
	return m_heap.size() - 1;
}

int main()
{
	std::cout << "Write a number that will be the initial value of the binary heap: ";
	int initialValue;
	std::cin >> initialValue;
	BinaryHeap binaryHeap(initialValue);

	while(true)
	{
		std::cout << "\nSelect an option   1- Peek    2- Size    3- Add value    4- Remove by value    5- Remove by index    6- Poll    7- Print Heap   :";
		int choice;
		std::cin >> choice;

		switch(choice)
		{
		case 1:
			binaryHeap.Peek();
			break;

		case 2:
			binaryHeap.Size();
			break;

		case 3:
			std::cout << "\nValue to add: ";
			int valueToAdd;
			std::cin >> valueToAdd;
			binaryHeap.Add(valueToAdd);
			break;

		case 4:
			std::cout << "\nValue to remove: ";
			int valueToRemove;
			std::cin >> valueToRemove;
			binaryHeap.RemoveValue(valueToRemove);
			break;

		case 5:
			std::cout << "\nIndex to remove: ";
			int IndexToRemove;
			std::cin >> IndexToRemove;
			binaryHeap.RemoveIndex(IndexToRemove);
			break;

		case 6:
			binaryHeap.Poll();
			break;

		case 7:
			binaryHeap.PrintHeap();
			break;

		default:
			throw std::exception("Illegal choice!");
		}

	}
}