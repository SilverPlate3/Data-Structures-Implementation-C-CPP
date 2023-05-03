#include <iostream>
#include "LRU Cache.h"
#include "Process.h"

int UserInputMaxCapacity()
{
    std::cout << "LRU max capacity: ";
    int maxCapacity;
    std::cin >> maxCapacity;
    return maxCapacity;
}

int UserInputOperation()
{
    std::cout << "\nSelect operation:   1) Insert     2) Query     3) Print LRU cache by order  : ";
    int choice;
    std::cin >> choice;
    return choice;
}

int main()
{
    const auto maxCapacity = UserInputMaxCapacity();

    LRU<int, Process> lru(maxCapacity);

    while (true)
    {
        const auto choice = UserInputOperation();
        switch (choice)
        {
        case 1:
        {
            auto pidToInsert = Process::UserInputPid();
            Process process;
            std::cout << "process was added: " << std::boolalpha << lru.Put(pidToInsert, process) << std::endl;
            break;
        }

        case 2:
        {
            auto pidToQuery = Process::UserInputPid();
            auto optionalProcess = lru.Get(pidToQuery);
            if (optionalProcess)
            {
                std::cout << "\nPID: " << pidToQuery << " Process stats: " << optionalProcess.value() << std::endl;
            }
            else
            {
                std::cout << "PID not found!" << std::endl;
            }
            break;
        }

        case 3:
            lru.PrintCache();
            break;
        }
    }
}