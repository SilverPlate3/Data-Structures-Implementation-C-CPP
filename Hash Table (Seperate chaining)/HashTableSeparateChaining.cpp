#include "HashTableSeparateChaining.h"
#include <algorithm>


HashTable::HashTable()
{
	m_table.resize(m_capacity);
}

bool HashTable::Contains(const std::string& value)
{
	const auto key = Hash(value);
	const auto& bucket = m_table.at(key);

	return IsValueInBucket(value, bucket);
}

void HashTable::NewTable()
{
	std::vector<std::vector<std::string>> newTable;
	m_capacity *= 2;
	newTable.resize(m_capacity);
	m_threshold = m_capacity * m_loadFactor;
	m_currentNumberOfElements = 0;

	std::vector<std::vector<std::string>> tempTable(std::move(m_table));
	m_table = std::move(newTable);

	for (auto& bucket : tempTable)
	{
		for (auto& string : bucket)
		{
			Insert(string);
		}
	}
}

void  HashTable::Insert(std::string& value)
{
	const auto key = Hash(value);
	auto& bucket = m_table.at(key);

	if (IsValueInBucket(value, bucket))
	{
		return;
	}

	bucket.emplace_back(std::move(value));
	m_currentNumberOfElements++;

	if (bucket.size() == 3 || m_currentNumberOfElements > m_threshold)
	{
		NewTable();
	}
}

void HashTable::Remove(const std::string& value)
{
	const auto key = Hash(value);
	auto& bucket = m_table.at(key);

	const auto& it = std::find(bucket.begin(), bucket.end(), value);
	if (it != bucket.end())
	{
		bucket.erase(it);
		m_currentNumberOfElements--;
	}
}

int HashTable::Hash(const std::string& value)
{
	long long hashValue = static_cast<int>(value.size());
	for (const auto& character : value)
	{
		hashValue *= character;
		hashValue += character;
	}

	return hashValue % m_capacity;
}

bool HashTable::IsValueInBucket(const std::string& value, const std::vector<std::string>& bucket)
{
	return std::any_of(bucket.cbegin(), bucket.cend(),
		[&](const std::string& string) {return string == value; });
}

void HashTable::PrintTable()
{
	std::cout << "Capacity: " << m_capacity << std::endl;
	for (int i = 0; i < m_capacity; i++)
	{
		const auto& bucket = m_table.at(i);
		if (bucket.empty())
		{
			continue;
		}

		std::cout << "\nKey: " << i << "  Value: ";
		for (const auto& string : bucket)
		{
			std::cout << string << "  ";
		}
	}
}


int main()
{
	HashTable hashTable;

	while (true)
	{
		std::cout << "\nSelect an option   1- Insert    2- Remove    3- Contains     4- Print Table :";
		int choice;
		std::cin >> choice;

		switch (choice)
		{
		case 1:
		{
			std::cout << "\nValue to insert: ";
			std::string valueToAdd;
			std::cin >> valueToAdd;
			hashTable.Insert(valueToAdd);
		}
		break;

		case 2:
		{
			std::cout << "\nValue to Remove: ";
			std::string valueToRemove;
			std::cin >> valueToRemove;
			hashTable.Remove(valueToRemove);
		}
		break;

		case 3:
		{
			std::cout << "\nValue to Find: ";
			std::string valueToFind;
			std::cin >> valueToFind;
			std::cout << "The HashTable contains " << valueToFind << ": " << std::boolalpha << hashTable.Contains(valueToFind) << std::endl;
		}
		break;

		case 4:
			hashTable.PrintTable();
			break;
		}
	}

	return 0;
}