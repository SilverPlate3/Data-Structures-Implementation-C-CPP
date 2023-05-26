#pragma once
#include <vector>

template <typename T>
void QuickSort(std::vector<T>& vectorToSort, int leftIndex, int rightIndex)
{	
	if (leftIndex >= rightIndex)
	{
		return;
	}

	int i = leftIndex - 1;
	for (int j = leftIndex; j < rightIndex; ++j)
	{
		if (vectorToSort[j] < vectorToSort[rightIndex])
		{
			++i;
			std::swap(vectorToSort[j], vectorToSort[i]);
		}
	}
	++i;
	std::swap(vectorToSort[rightIndex], vectorToSort[i]);

	QuickSort(vectorToSort, leftIndex, i - 1);
	QuickSort(vectorToSort, i + 1, rightIndex);
}
