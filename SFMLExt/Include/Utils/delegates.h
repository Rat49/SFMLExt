#pragma once
#include <functional>

namespace ext
{
    void StartDefferedTask(std::uint32_t msBeforeStart, std::function<void()> task);
}
