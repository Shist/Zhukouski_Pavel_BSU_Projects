#include "StateMachine.hpp"

StateMachine::StateMachine (std::unordered_map <std::string, StateMachine::State> states, std::string initialStateName)
    : states_ (std::move (states)),
      currentStateName_ (std::move (initialStateName))
{
    EnterCurrentState ();
}

void StateMachine::Consume (char code)
{
    State &current = states_[currentStateName_];
    if (current.exits_.count (code) > 0)
    {
        currentStateName_ = current.exits_[code] ();
        EnterCurrentState ();
    }
    else
    {
        UnsupportedCodeException exception;
        exception << UnsupportedCodeException::CurrentStateCopy (current);
        exception << UnsupportedCodeException::InputCode (code);
        BOOST_THROW_EXCEPTION (exception);
    }
}

const std::string &StateMachine::GetCurrentStateName () const
{
    return currentStateName_;
}

void StateMachine::ValidateCurrentState () const
{
    if (states_.count (currentStateName_) == 0)
    {
        StateNotExistsException exception;
        exception << StateNotExistsException::StateName (currentStateName_);
        BOOST_THROW_EXCEPTION (exception);
    }
}

void StateMachine::EnterCurrentState ()
{
    ValidateCurrentState ();
    std::optional <char> fastForwardCode = states_[currentStateName_].enter_ (*this);

    if (fastForwardCode.has_value ())
    {
        Consume (fastForwardCode.value ());
    }
}
