#pragma once
#include <iostream>
#include <vector>

class HashTable
{
public:

	HashTable();
	void Insert(std::string& value);
	bool Contains(const std::string& value);
	void Remove(const std::string& value);
	void PrintTable();

private:
	bool IsValueInChain(const std::string& value, const std::vector<std::string>& chain);
	int Hash(const std::string& value);
	void NewTable();

private:
	int m_tableSize = 5;
	std::vector<std::vector<std::string>> m_table;
};