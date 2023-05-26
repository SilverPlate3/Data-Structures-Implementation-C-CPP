#pragma once
#include <vector>

template <typename T>
std::vector<T> BubbleSort(const std::vector<T>& vectorToSort)
{
	auto sortedVector = vectorToSort;

 	for (int i = 0; i < sortedVector.size(); ++i)
	{
		for (int j = 0; j < sortedVector.size() - 1 - i; ++j)
		{
			if(sortedVector.at(j) > sortedVector.at(j + 1))
			{
				std::swap(sortedVector.at(j), sortedVector.at(j + 1));
			}
		}
	}

	return sortedVector;
}