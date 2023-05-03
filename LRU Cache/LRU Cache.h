#include <map>
#include <list>
#include <iostream>
#include <optional>

template<typename Tkey, typename Tvalue>
class LRU
{
	using templateList = std::list<std::pair<Tkey, Tvalue>>;
	using templateListIt = typename std::list<std::pair<Tkey, Tvalue>>::iterator;
public:

	LRU(int maxCapacity)
		: m_maxCacheCapacity(maxCapacity){}

	void PrintCache()
	{
		std::cout << "\n======================= Cache ========================" << std::endl;
		for(auto& pair : m_valuesList)
		{
			std::cout << pair.second << std::endl;
		}
	}

	std::optional<Tvalue> Get(const Tkey& key)
	{
		auto mapIt = m_iteratorsMap.find(key);
		if (mapIt == m_iteratorsMap.end())
		{
			return std::nullopt;
		}

		auto& listIt = mapIt->second;
		MoveToBeginningOfList(listIt);
		return listIt->second;
	}

	bool Put(const Tkey& key, const Tvalue& value)
	{
		auto mapIt = m_iteratorsMap.find(key);
		if (mapIt != m_iteratorsMap.end())
		{
			MoveToBeginningOfList(mapIt->second);
			return false;
		}

		if(m_counter == m_maxCacheCapacity)
		{
			DeleteLeastRecentlyUsedNode();
		}

		InsertNewValue(key, value);
		m_counter++;
		return true;
	}

private:

	void MoveToBeginningOfList(const templateListIt& listIt)
	{
		if (listIt != m_valuesList.begin())
		{
			m_valuesList.splice(m_valuesList.begin(), m_valuesList, listIt);
		}
	}

	void DeleteLeastRecentlyUsedNode()
	{
		auto& lastElement = m_valuesList.back();
		m_iteratorsMap.erase(lastElement.first);
		m_valuesList.pop_back();
		m_counter--;
	}

	void InsertNewValue(const Tkey& key, const Tvalue& value)
	{
		auto listIt = m_valuesList.insert(m_valuesList.begin(), std::make_pair(key, value));
		m_iteratorsMap.insert({ key, listIt });
	}

private:

	unsigned long m_maxCacheCapacity;
	unsigned long m_counter;
	templateList m_valuesList;
	std::map<Tkey, templateListIt> m_iteratorsMap;
};