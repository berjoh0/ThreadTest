#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "TaskManager/TaskManager.h"
#include "TaskManager/Task.h"

// using namespace std;

class ThreadTest
{
public:
    void Start()
    {
        std::cout << "Starting ThreadTest" << std::endl;
        taskManager.Start();
        running = true;

        while (running)
        {
            std::string cmd{""};

            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Enter command: ";
            std::cin >> cmd;

            if (cmd == "?")
            {
                // Help
                printHelp();
            }
            else if (cmd == "q")
            {
                taskManager.AddTask(Task{"q", 0, 0});
                while (taskManager.IsRunning())
                {
                    std::cout << "TaskManager still running, wait " << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }

                running = false;
            }
            else if (cmd == "l")
            {
                taskManager.PrintList();
            }
            else if (cmd == "s")
            {
                int tLoops = 0;
                std::cout << "Loops: ";
                std::cin >> tLoops;

                int tSleepTime = 0;
                std::cout << "TimeSleep: ";
                std::cin >> tSleepTime;
                taskManager.AddTask(Task{"s", tLoops, tSleepTime});
            }
            else
            {
                std::cout << "Invalid command" << std::endl;
            }
        }
    }

private:
    bool running = false;
    TaskManager taskManager{};

    void printHelp()
    {
        std::cout << "Help: " << std::endl;
        std::cout << "? -Help " << std::endl;
        std::cout << "q -Quit " << std::endl;
        std::cout << "s -Start loop, arguments loops, sleep in sec " << std::endl;
    }
};

int main()
{
    std::cout << "Threadtest" << std::endl;

    ThreadTest tt{};

    tt.Start();

    return 0;
}
