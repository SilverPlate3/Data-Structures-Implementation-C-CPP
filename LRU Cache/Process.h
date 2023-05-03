#pragma once
#include <iostream>

class Process
{
public:
    Process();
    static int UserInputPid();
    friend std::ostream& operator<<(std::ostream& os, const Process& processData);

private:
    std::string m_ProcessName;
    std::string m_cmd;
};
