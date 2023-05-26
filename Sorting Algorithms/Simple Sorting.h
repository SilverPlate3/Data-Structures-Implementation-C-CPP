#pragma once
#include <vector>

template <typename T>
std::vector<T> SimpleSort(const std::vector<T>& vectorToSort)
{
	auto sortedVector = vectorToSort;

	for(int i = 0; i < sortedVector.size(); ++i)
	{
		for(int j = i + 1; j < sortedVector.size(); ++j)
		{
			if(sortedVector.at(i) > sortedVector.at(j))
			{
				std::swap(sortedVector.at(i), sortedVector.at(j));
			}
		}
	}

	return sortedVector;
}










