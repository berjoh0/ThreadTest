#include <iostream>
#include <chrono>
#include <thread>
#include "TaskManager.h"
#include "TaskLoop.h"

TaskManager::TaskManager()
{
    std::cout << "TaskManager created" << std::endl;
}

TaskManager::~TaskManager()
{
    std::cout << "TaskManager destruct" << std::endl;
    shutdown();
}

void TaskManager::Start()
{
    std::cout << "TaskManager Starting" << std::endl;

    if (tm_thread.joinable())
    {
        std::cout << "TaskManager Already running" << std::endl;
    }

    taskQueue.clear();
    tm_thread = std::thread(&TaskManager::run, this);
}

void TaskManager::PrintList()
{
    std::cout << "TaskManager Main Thread List " << std::endl;
    for (int i = 0; i < tasks.size(); i++)
    {
        TaskLoop tl = tasks.at(i);
        std::cout << "      " << tl.GetID() << ": " << tl.IsRunning();
    }
}

void TaskManager::AddTask(Task task)
{
    std::cout << "TaskManager execute " << task.getCommand() << std::endl;
    taskQueue.push_back(task);
}

bool TaskManager::IsRunning()
{
    return running;
}

void TaskManager::run()
{
    std::cout << "TaskManager Main Thread Running" << std::endl;

    running = true;

    while (running)
    {

        // Check for non running.
        for (int i = 0; i < tasks.size(); i++)
        {
            TaskLoop tl = tasks.at(i);

            if (!tl.IsRunning())
            {
                tasks.erase(tasks.begin() + i);
            }
        }

        if (taskQueue.size() == 0)
            continue;

        std::cout << "TaskManager Main Thread: StartTask " << taskQueue[0].getCommand() << std::endl;
        if (taskQueue[0].getCommand() == "s")
        {
            startTask(taskQueue[0]);
        }
        else if (taskQueue[0].getCommand() == "q")
        {
            // Check for running sub tasks;
            for (int i = 0; i < tasks.size(); i++)
            {
                TaskLoop tl = tasks.at(i);

                if (tl.IsRunning())
                {
                    tl.Abort();
                }
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
            running = false;
        }
        taskQueue.pop_front();
    }
    std::cout << "TaskManager Main Thread Stopped" << std::endl;
}

void TaskManager::startTask(Task task)
{
    std::cout << "TaskManager startTask" << std::endl;
    tasks.push_back(std::move(TaskLoop(taskLoopID, task.getLoops(), task.getSleepTime())));
    taskLoopID++;
}

void TaskManager::shutdown()
{
    if (tm_thread.joinable())
    {
        running = false;
        tm_thread.detach();
    }
    std::cout << "TaskManager shutdown" << std::endl;
}
