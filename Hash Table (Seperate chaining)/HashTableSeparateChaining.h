#pragma once
#include <iostream>
#include <vector>

class HashTable
{
public:
	HashTable();
	bool Contains(const std::string& value);
	void  Insert(std::string& value);
	void Remove(const std::string& value);
	void PrintTable();

private:
	void NewTable();
	int Hash(const std::string& value);
	bool IsValueInBucket(const std::string& value, const std::vector<std::string>& bucket);

private:
	int m_capacity = 4;
	double m_loadFactor = 0.75;
	int m_threshold = m_capacity * m_loadFactor;
	int m_currentNumberOfElements{};
	std::vector<std::vector<std::string>> m_table;

};
