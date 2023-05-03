#include <iostream>
#include "Process.h"

Process::Process()
{
    std::cout << "\nProcess name: ";
    std::cin >> m_ProcessName;

    std::cout << "\nCmd: ";
    std::cin >> m_cmd;
}

int Process::UserInputPid()
{
    std::cout << "\nPID: ";
    int pid;
    std::cin >> pid;
    return pid;
}

std::ostream& operator<<(std::ostream& os, const Process& processData)
{
    os << processData.m_ProcessName << "  " << processData.m_cmd << std::endl;
    return os;
}