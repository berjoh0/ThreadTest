#include <thread>
#include <deque>
#include "TaskLoop.h"
#include "Task.h"

class TaskManager
{

public:
    TaskManager();
    ~TaskManager();

    void AddTask(Task task);
    bool IsRunning();
    void Start();
    void PrintList();

private:
    std::thread tm_thread;
    std::deque<Task> taskQueue{};
    std::deque<TaskLoop> tasks{};
    int taskLoopID{0};

    bool running = false;
    void run();
    void startTask(Task task);
    void shutdown();
};