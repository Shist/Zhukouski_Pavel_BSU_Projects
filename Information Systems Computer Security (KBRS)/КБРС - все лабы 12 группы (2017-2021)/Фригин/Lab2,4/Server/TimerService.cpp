#include "TimerService.hpp"

std::priority_queue <TimerService::Callback, std::vector <TimerService::Callback>,
                     std::greater <TimerService::Callback>> TimerService::callbacks_ {};

bool TimerService::Callback::operator< (const TimerService::Callback &rhs) const
{
    return executionTime_ < rhs.executionTime_;
}

bool TimerService::Callback::operator> (const TimerService::Callback &rhs) const
{
    return rhs < *this;
}

bool TimerService::Callback::operator<= (const TimerService::Callback &rhs) const
{
    return !(rhs < *this);
}

bool TimerService::Callback::operator>= (const TimerService::Callback &rhs) const
{
    return !(*this < rhs);
}

void TimerService::Step ()
{
    clock_t current = clock ();
    std::vector <Callback> reschedule;

    while (!callbacks_.empty () && callbacks_.top ().executionTime_ <= current)
    {
        Callback top = callbacks_.top ();
        callbacks_.pop ();

        if (!top.callback_ ())
        {
            reschedule.emplace_back (top);
        }
    }

    for (const Callback &callback : reschedule)
    {
        AddTimer (callback);
    }
}

void TimerService::AddTimer (TimerService::Callback callback)
{
    callbacks_.emplace (std::move (callback));
}

void TimerService::RemoveAllTimers (CallbackOwnerId fromOwner)
{
    std::priority_queue <Callback, std::vector <Callback>, std::greater <Callback>> queueCopy;
    std::swap (queueCopy, callbacks_);

    while (!queueCopy.empty ())
    {
        Callback top = queueCopy.top ();
        queueCopy.pop ();

        if (top.owner_ != fromOwner)
        {
            AddTimer (top);
        }
    }
}
