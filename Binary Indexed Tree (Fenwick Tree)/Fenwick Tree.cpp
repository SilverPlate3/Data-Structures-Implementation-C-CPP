#include <iostream>
#include "Fenwick Tree.h"

FenwickTree::FenwickTree(int size)
{
	m_originalArray.resize(size);
	m_FenwickTreeArray.resize(size + 1);
	InitializeArrays();
	ConstructFenwickArray();
}

void FenwickTree::InitializeArrays()
{
	m_FenwickTreeArray.at(0) = 0;
	for (int i = 0, j = 1; i < m_originalArray.size(); i++, j++)
	{
		std::cout << "Value at index " << i << ":  ";
		int value;
		std::cin >> value;
		m_originalArray.at(i) = value;
		m_FenwickTreeArray.at(j) = value;
	}
}

void FenwickTree::ConstructFenwickArray()
{
	for (int i = 1; i <= m_FenwickTreeArray.size(); i++)
	{
		auto hopUpIndex = i + GetValueOfLeastSignificantBitThatIsOne(i);
		if (hopUpIndex < m_FenwickTreeArray.size())
		{
			m_FenwickTreeArray.at(hopUpIndex) += m_FenwickTreeArray.at(i);
		}
	}
}

void FenwickTree::UpdateValueAtIndex(int newValue, int index)
{
	auto difference = m_originalArray.at(index) - newValue;
	auto value = difference * -1;
	m_originalArray.at(index) = newValue;
	PointUpdate(value, index + 1);
}

void FenwickTree::PointUpdate(int value, int index)
{
	if (index <= m_FenwickTreeArray.size())
	{
		m_FenwickTreeArray.at(index) += value;
		auto hopUpIndex = index + GetValueOfLeastSignificantBitThatIsOne(index);
		PointUpdate(value, hopUpIndex);
	}
}

int FenwickTree::RangeSumQuery(int startIndex, int endIndex)
{
	auto bigSum = FromIndexToZeroSum(endIndex);
	auto smallSum = FromIndexToZeroSum(startIndex);
	return bigSum - smallSum;
}

int  FenwickTree::FromIndexToZeroSum(int index)
{
	if (index >= 1)
	{
		auto hopDownindex = index - GetValueOfLeastSignificantBitThatIsOne(index);
		return m_FenwickTreeArray.at(index) + FromIndexToZeroSum(hopDownindex);
	}
}

int FenwickTree::GetValueOfLeastSignificantBitThatIsOne(const int number)
{
	return number & -number;
}

void FenwickTree::PrintArrays()
{
	std::cout << "\n\nOriginal array:  ";
	for (int i = 0; i < m_originalArray.size(); i++)
	{
		std::cout << m_originalArray.at(i) << ", ";
	}

	std::cout << "\nFenwick array:  ";
	for (int j = 1; j < m_FenwickTreeArray.size(); j++)
	{
		std::cout << m_FenwickTreeArray.at(j) << ", ";
	}
}


int main()
{
	std::cout << "Array size: ";
	int arraySize;
	std::cin >> arraySize;
	FenwickTree ft(arraySize);

	int choice;
	while(true)
	{
		std::cout << "\nSelect operation     1- Range Sum Query (none inclusive)        2- Range Sum Query (inclusive)        3- Update value at index         4- Print arrays  : ";
		std::cin >> choice;

		switch (choice)
		{
		case 1:
		case 2:
			{
				int startIndex, endIndex;
				std::cout << "\nFrom index: ";
				std::cin >> startIndex;
				std::cout << "\nTo index: ";
				std::cin >> endIndex;
				auto sum = (choice == 1) ? ft.RangeSumQuery(startIndex, endIndex) : ft.RangeSumQuery(startIndex, endIndex + 1);
				std::cout << "The sum from index " << startIndex << " to index " << endIndex << " is: " << sum << std::endl;
				break;
			}
		case 3:
			{
				int newValue, index;
				std::cout << "\nNew value: ";
				std::cin >> newValue;
				std::cout << "\nAt index: ";
				std::cin >> index;
				ft.UpdateValueAtIndex(newValue, index);
				break;
			}
		case 4:
			ft.PrintArrays();
			break;
		}
	}
}

