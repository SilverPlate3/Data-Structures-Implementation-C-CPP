#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>


class BinaryHeap
{
public:

	BinaryHeap(int initialValue)
	{
		Add(initialValue);
	}

	void Peek()
	{
		if(m_heap.empty())
		{
			std::cout << "Heap is empty!" << std::endl;
		}
		else
		{
			std::cout << "Heap Root value: " << m_heap.at(0) << std::endl;
		}
	}

	void Poll()
	{
		RemoveIndex(0);
	}

	void Size()
	{
		std::cout << "Heap size: " << m_heap.size() << std::endl;
	}

	void Add(int value)
	{
		m_heap.emplace_back(value);
		MapAdd(value, LastIndex());
		BubbleUp(LastIndex()); 
	}

	void RemoveValue(int value)
	{
		if(!IsContainsValue(value))
		{
			std::cout << "The heap doesn't contain the value: " << value << std::endl;
			return;
		}

		auto index = MapGetIndexOf(value);
		RemoveIndex(index);
	}

	void RemoveIndex(int index)
	{
		if(index > LastIndex())
		{
			std::cout << "The heap doesn't contain the index: " << index << std::endl;
			return;
		}

		auto valueToRemove = m_heap.at(index);
		SwapNodes(index, LastIndex());

		auto lastIndexBeforeRemoval = LastIndex();
		m_heap.pop_back();
		MapRemove(valueToRemove, lastIndexBeforeRemoval);

		if(index == lastIndexBeforeRemoval)
		{
			return;
		}

		// TODO - He said he was laizy here. Try to implement the not lazy
		auto value = m_heap.at(index);
		BubbleDown(index);
		if(m_heap.at(index) == value)
		{
			BubbleUp(index);
		}
	}

	void PrintHeap()
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

private:

	bool IsContainsValue(int value)
	{
		return m_map.count(value);
	}

	int LastIndex()
	{
		return m_heap.size() - 1;
	}

	void BubbleUp(int index)
	{
		int parent = (index - 1) / 2;
		while (index > ROOT_NODE_INDEX && IsNodeSmaller(index, parent))
		{
			SwapNodes(parent, index);
			index = parent;
			parent = (index - 1) / 2;
		}
	}

	void BubbleDown(int index)
	{
		while (true)
		{
			int leftChildIndex = 2 * index + 1;
			int rightChildIndex = 2 * index + 2;
			int smallestChild = ((rightChildIndex < LastIndex()) && IsNodeSmaller(rightChildIndex, leftChildIndex)) ? rightChildIndex : leftChildIndex;
			if(leftChildIndex > LastIndex() || IsNodeSmaller(index, smallestChild))
			{
				break;
			}

			SwapNodes(smallestChild, index);
			index = smallestChild;
		}
	}

	void SwapNodes(int indexA, int indexB)
	{
		auto valueAtIndexA = m_heap.at(indexA);
		auto valueAtIndexB = m_heap.at(indexB);

		m_heap.at(indexA) = valueAtIndexB;
		m_heap.at(indexB) = valueAtIndexA;

		SwapNodesMap(indexA, valueAtIndexA, indexB, valueAtIndexB);
	}

	void SwapNodesMap(int indexA, int valueAtIndexA, int indexB, int valueAtIndexB)
	{
		auto& mapValueA = m_map.at(valueAtIndexA);
		auto& mapValueB = m_map.at(valueAtIndexB);

		mapValueA.erase(indexA);
		mapValueB.erase(indexB);

		mapValueA.insert(indexB);
		mapValueB.insert(indexA);
	}

	bool IsNodeSmaller(int index1, int index2)
	{
		return (m_heap.at(index1) < m_heap.at(index2)) ? true : false;
	}

	void MapRemove(int value, int index)
	{
		auto mapIterator = m_map.find(value);
		auto setIterator = mapIterator->second.find(index);
		mapIterator->second.erase(setIterator);
		if(mapIterator->second.empty())
		{
			m_map.erase(mapIterator);
		}
	}

	void MapAdd(int value, int index)
	{
		auto mapIterator = m_map.find(value);
		if(mapIterator == m_map.end())
		{
			m_map[value] = std::set<int>{ index };
		}
		else
		{
			mapIterator->second.emplace(index);
		}
	}

	int MapGetIndexOf(int value)
	{
		return *m_map.at(value).begin();
	}


private:
	std::vector<int> m_heap;
	std::unordered_map<int, std::set<int>> m_map;
	const int ROOT_NODE_INDEX = 0;
};


int main()
{
	BinaryHeap binaryHeap(9);
	binaryHeap.Add(5);
	binaryHeap.Add(6);
	binaryHeap.Peek();
	binaryHeap.Add(3);
	binaryHeap.Add(11);
	binaryHeap.PrintHeap();
	binaryHeap.Poll();
	binaryHeap.PrintHeap();
	binaryHeap.Add(7);
	binaryHeap.Add(9);
	binaryHeap.PrintHeap();
	binaryHeap.RemoveValue(4);
	binaryHeap.RemoveValue(6);
	binaryHeap.RemoveIndex(2);
	binaryHeap.Poll();
	binaryHeap.PrintHeap();
	binaryHeap.Add(8);
	binaryHeap.Add(8);
	binaryHeap.Add(8);
	binaryHeap.Add(12);
	binaryHeap.Add(1);
	binaryHeap.PrintHeap();
	binaryHeap.Peek();
	binaryHeap.RemoveIndex(34);
}