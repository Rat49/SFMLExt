#include <Utils\delegates.h>
#include <thread>
#include <chrono>

void ext::StartDefferedTask(std::uint32_t msBeforeStart, std::function<void()> task)
{
    std::thread taskThread(
        [=]
        {
            std::chrono::milliseconds duration(msBeforeStart);
            std::this_thread::sleep_for(duration);
            task();
        });

    taskThread.detach();
}

#include <algorithm>

namespace ext
{
    void StartDefferedTask(std::uint32_t msBeforeStart, std::function<void()> task)
    {
        std::thread([msBeforeStart, task]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(msBeforeStart));
            task();
        }).detach();
    }
}