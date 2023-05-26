#include "Simple Sorting.h"
#include "Selection Sort.h"
#include "Bubble Sort.h"
#include "InsertionSort.h"
#include "Quick Sort.h"
#include <iostream>

template <typename T>
void PrintInputAndOutput(const std::vector<T>& input, const std::vector<T>& output)
{
	std::cout << "\n\nInput: ";
	for (const auto& element : input)
	{
		std::cout << element << ", ";
	}

	std::cout << "\nOutput: ";
	for (const auto& element : output)
	{
		std::cout << element << ", ";
	}

}

int main()
{
	const std::vector<int> vectorToSort{ 7, 34, 2, -3, 0, 2, 9, 14, 33, -12, -9, 78, 77 };

	auto sortedVector = SimpleSort(vectorToSort);
	PrintInputAndOutput(vectorToSort, sortedVector);

	sortedVector = SelectionSort(vectorToSort);
	PrintInputAndOutput(vectorToSort, sortedVector);

	sortedVector = BubbleSort(vectorToSort);
	PrintInputAndOutput(vectorToSort, sortedVector);

	sortedVector = InsertionSort(vectorToSort);
	PrintInputAndOutput(vectorToSort, sortedVector);

	sortedVector = vectorToSort;
	QuickSort(sortedVector, 0 , vectorToSort.size() - 1);
	PrintInputAndOutput(vectorToSort, sortedVector);
}