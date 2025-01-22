#include <thread>
#pragma once
class TaskLoop
{

public:
    TaskLoop() = default;
    TaskLoop(int id, int loops, int sleepTime);
    ~TaskLoop();
    void Start(int loops, int sleepTime);
    int GetID();
    void Abort();
    bool IsRunning();

private:
    std::thread tloop_thread;
    int id;
    bool running{false};
    bool abort{false};
    void run(int loops, int sleepTime);
};