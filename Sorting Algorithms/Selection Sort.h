#pragma once
#include <vector>

template <typename T>
std::vector<T> SelectionSort(const std::vector<T>& vectorToSort)
{
	auto sortedVector = vectorToSort;

	for (int i = 0; i < sortedVector.size(); ++i)
	{
		int indexWithSmallestValue = i;
		for (int j = i + 1; j < sortedVector.size(); ++j)
		{
			indexWithSmallestValue = sortedVector.at(indexWithSmallestValue) < sortedVector.at(j) ? indexWithSmallestValue : j;
		}

		std::swap(sortedVector.at(i), sortedVector.at(indexWithSmallestValue));
	}

	return sortedVector;
}