#include <thread>
#include <chrono>
#include <iostream>
#include "TaskLoop.h"

TaskLoop::TaskLoop()
{
}

TaskLoop::TaskLoop(int id, int loops, int sleepTime)
{
    std::cout << "TaskLoop Constructor " << id << " " << loops << " " << sleepTime;
    TaskLoop::id = id;
    // TaskLoop::Start(loops, sleepTime);
    std::thread tl_thread = std::thread(&TaskLoop::run, TaskLoop(), loops, sleepTime);
}

TaskLoop::~TaskLoop()
{
}

void TaskLoop::Start(int loops, int sleepTime)
{
    std::cout << "TaskLoop Start " << id << " " << loops << " " << sleepTime;
    running = true;

    try
    {
        // run(loops, sleepTime);
        std::thread tl_thread = std::thread(&TaskLoop::run, TaskLoop(), loops, sleepTime);
        /*        while (running)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }*/
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

int TaskLoop::GetID()
{
    return id;
}

void TaskLoop::Abort()
{
    abort = true;
}

bool TaskLoop::IsRunning()
{
    return running;
}

void TaskLoop::run(int loops, int sleepTime)
{
    for (int i = 0; i < loops; i++)
    {
        std::cout << "TaskLoop " << TaskLoop::id << " : " << i << " " << loops << " " << sleepTime;
        std::this_thread::sleep_for(std::chrono::seconds(sleepTime));
        if (abort)
        {
            std::cout << "TaskLoop ABORT! " << TaskLoop::id << " : " << i << " " << loops << " " << sleepTime;
            break;
        }
    }
    running = false;
}
