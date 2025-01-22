#include <string>
#include "Task.h"

Task::Task(std::string command, int loops, int sleepTime)
{
    Task::command = command;
    Task::loops = loops;
    Task::sleepTime = sleepTime;
}

std::string Task::getCommand()
{
    return Task::command;
}
int Task::getLoops()
{
    return Task::loops;
}

int Task::getSleepTime()
{
    return Task::sleepTime;
}
