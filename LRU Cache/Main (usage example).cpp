#include <iostream>
#include "LRU Cache.h"

class Process
{
public:
	Process(const std::string& processName, const std::string& cmd)
		:m_ProcessName(processName), m_cmd(cmd){}

    friend std::ostream& operator<<(std::ostream& os, const Process& processData);

private:
	std::string m_ProcessName;
	std::string m_cmd;
};

std::ostream& operator<<(std::ostream& os, const Process& processData)
{
    os << processData.m_ProcessName << "  " << processData.m_cmd << std::endl;
    return os;
}

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

Process CreateProcess()
{
    std::cout << "\nProcess name: ";
    std::string processName;
    std::cin >> processName;

    std::cout << "\nCmd: ";
    std::string cmd;
    std::cin >> cmd;

    return (Process{ processName, cmd });
}

int UserInputPid()
{
    std::cout << "\nPID: ";
    int pid;
    std::cin >> pid;
    return pid;
}

int main()
{
	const auto maxCapacity = UserInputMaxCapacity();

    LRU<int, Process> lru(maxCapacity);

    while(true)
    {
	    const auto choice = UserInputOperation();
        switch(choice)
        {
        case 1:
        {
            auto process = CreateProcess();
            auto pidToInsert = UserInputPid();
            std::cout << "process was added: " << std::boolalpha << lru.Put(pidToInsert, process) << std::endl;
            break;
        }

        case 2:
        {
            auto pidToQuery = UserInputPid();
            auto optionalProcess = lru.Get(pidToQuery);
            if(optionalProcess)
            {
                std::cout << "\nPID: " << pidToQuery << " Process stats: " << *(optionalProcess.value()) << std::endl;
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