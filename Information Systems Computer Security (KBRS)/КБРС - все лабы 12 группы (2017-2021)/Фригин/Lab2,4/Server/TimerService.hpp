#pragma once
#include <unordered_map>
#include <ctime>
#include <functional>
#include <queue>

class TimerService
{
public:
    using CallbackOwnerId = void *;

    struct Callback
    {
        CallbackOwnerId owner_;
        std::clock_t executionTime_;
        std::function <bool ()> callback_;

        bool operator< (const Callback &rhs) const;
        bool operator> (const Callback &rhs) const;
        bool operator<= (const Callback &rhs) const;
        bool operator>= (const Callback &rhs) const;
    };

    static void Step ();
    static void AddTimer (Callback callback);
    static void RemoveAllTimers (CallbackOwnerId fromOwner);

private:
    static std::priority_queue <Callback, std::vector <Callback>, std::greater <Callback>> callbacks_;
};
