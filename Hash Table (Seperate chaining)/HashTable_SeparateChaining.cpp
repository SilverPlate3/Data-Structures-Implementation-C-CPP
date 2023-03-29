#include "HashTable_SeparateChaining.h"
#include <algorithm>

HashTable::HashTable()
{
	m_table.resize(m_tableSize);
}

void HashTable::Insert(std::string& value)
{
	const auto key = Hash(value);
	auto& chain = m_table.at(key);

	if (IsValueInChain(value, chain))
	{
		return;
	}

	chain.emplace_back(std::move(value));

	if (chain.size() == 3)
	{
		NewTable();
	}
}

void HashTable::NewTable()
{
	std::vector<std::vector<std::string>> newTable;
	m_tableSize *= 10;
	newTable.resize(m_tableSize);

	std::vector<std::vector<std::string>> tempTable(std::move(m_table));
	m_table = std::move(newTable);

	for (auto& chain : tempTable)
	{
		for (auto& string : chain)
		{
			Insert(string);
		}
	}
}

bool HashTable::Contains(const std::string& value)
{
	const auto key = Hash(value);
	const auto& chain = m_table.at(key);

	return IsValueInChain(value, chain);
}

bool HashTable::IsValueInChain(const std::string& value, const std::vector<std::string>& chain)
{
	return std::any_of(chain.cbegin(), chain.cend(),
		[&](const std::string& string) {return string == value; });
}

void HashTable::Remove(const std::string& value)
{
	const auto key = Hash(value);
	auto& chain = m_table.at(key);

	const auto& it = std::find(chain.begin(), chain.end(), value);
	if (it != chain.end())
	{
		chain.erase(it);
	}
}

int HashTable::Hash(const std::string& value)
{
	long long hashValue = static_cast<int>(value.size());
	for(const auto& character : value)
	{
		hashValue *= character;
		hashValue += character;
	}

	return hashValue % m_tableSize;
}

void HashTable::PrintTable()
{
	for (int i = 0; i < m_tableSize; i++)
	{
		const auto& chain = m_table.at(i);
		if (m_table.at(i).empty())
		{
			continue;
		}

		std::cout << "\nKey: " << i << "  Value: ";
		for (const auto& string : chain)
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







