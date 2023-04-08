#pragma once
#include <vector>

class FenwickTree
{
public:
	FenwickTree(int size);
	void PrintArrays();
	void UpdateValueAtIndex(int newValue, int index);
	int RangeSumQuery(int startIndex, int endIndex);

private:

	int  FromIndexToZeroSum(int index);
	void PointUpdate(int value, int index);
	void InitializeArrays();
	void ConstructFenwickArray();
	int GetValueOfLeastSignificantBitThatIsOne(const int number);

private:
	std::vector<int> m_originalArray;
	std::vector<int> m_FenwickTreeArray;
};
