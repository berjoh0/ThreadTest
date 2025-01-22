#include <string>
#pragma once
class Task
{
public:
    Task(std::string command, int loops, int sleepTime);
    std::string getCommand();
    int getLoops();
    int getSleepTime();

private:
    std::string command;
    int loops;
    int sleepTime;
};