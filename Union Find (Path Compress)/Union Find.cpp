#include "Union Find.h"
#include <iostream>

void UnionFind::Union(int elementA, int elementB)
{
	auto rootA = Find(elementA);
	auto rootB = Find(elementB);

	if (rootA == rootB)
	{
		std::cout << "Both elements are already in the same group" << std::endl;
		return;
	}

	auto smaller = std::min(rootA, rootB);
	auto bigger = std::max(rootA, rootB);

	m_whoIsMyParent.at(smaller) = bigger;
	m_groupSizes.at(bigger) += m_groupSizes.at(smaller);
	m_groupSizes.erase(smaller);
	--m_numberOfGroups;
}

UnionFind::UnionFind(int numberOfElements) :
	m_numberOfElements(numberOfElements), m_numberOfGroups(numberOfElements)
{
	m_whoIsMyParent.reserve(numberOfElements);
	m_groupSizes.reserve(numberOfElements);
	for (int i = 0; i < numberOfElements; i++)
	{
		m_whoIsMyParent.push_back(i);
		m_groupSizes[i] = 1;
	}
}

int UnionFind::Find(int element)
{
	auto originalElementValue = element;

	while (m_whoIsMyParent.at(element) != element)
	{
		element = m_whoIsMyParent.at(element);
	}

	PathCompression(element, originalElementValue);
	return element;
}

void UnionFind::PathCompression(int rootElement, int element)
{
	while (rootElement != element)
	{
		auto currentParent = m_whoIsMyParent.at(element);
		m_whoIsMyParent.at(element) = rootElement;
		element = currentParent;
	}
}

void UnionFind::PrintUnionFind()
{
	std::cout << "\nElement: ";
	for(int i = 0; i < m_numberOfElements; i++)
	{
		std::cout << i << "  ";
	}

	std::cout << "\nParent: ";
	for(auto val : m_whoIsMyParent)
	{
		std::cout << val << "  ";
	}
}

int UnionFind::GroupSize(int element)
{
	auto root = Find(element);
	return m_groupSizes.at(root);
}

int UnionFind::NumberOfGroups()
{
	return m_numberOfGroups;
}


int main()
{
	std::cout << "Size of Union Find: ";
	int unionFindSize;
	std::cin >> unionFindSize;
	UnionFind unionFind(unionFindSize);

	while(true)
	{
		std::cout << "\nSelect an option   1- Find group of element    2- Union two elements    "
			    << "3- Group Size of an element    4- Number Of Groups    5- Print Union Find    :";
		int choice;
		std::cin >> choice;

		int value;
		switch (choice)
		{
		case 1:
			std::cout << "Value: ";
			std::cin >> value;
			std::cout << "The group's root of: " << value << " is: " << unionFind.Find(value) << std::endl;
			break;

		case 2:
			int element1, element2;
			std::cout << "Element1: ";
			std::cin >> element1;
			std::cout << "Element2: ";
			std::cin >> element2;
			unionFind.Union(element1, element2);
			break;

		case 3:
			std::cout << "Value: ";
			std::cin >> value;
			std::cout << "The group size of element: " << value << " is: " << unionFind.GroupSize(value) << std::endl;
			break;

		case 4:
			std::cout << "Number of groups: " << unionFind.NumberOfGroups();
			break;

		case 5:
			std::cout << "\n=============== UNION FIND ===============" << std::endl;
			unionFind.PrintUnionFind();
			break;
		}

	}
}