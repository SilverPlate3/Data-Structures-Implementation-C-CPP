#pragma once
#include <vector>

template <typename T>
std::vector<T> InsertionSort(const std::vector<T>& vectorToSort)
{
	auto sortedVector = vectorToSort;

	for (int i = 1; i < sortedVector.size(); ++i)
	{
		T value = sortedVector.at(i);
		int j = i - 1;
		while(j >= 0 && sortedVector.at(j) >= value)
		{
			std::swap(sortedVector.at(j), sortedVector.at(j + 1));
			--j;
		}
	}

	return sortedVector;
}
