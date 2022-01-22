#pragma once
#include <functional>
#include <vector>
#include <unordered_map>
#include <optional>

#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>

class StateMachine final
{
public:
    struct State
    {
        std::function <std::optional <char> (StateMachine &owner)> enter_;
        std::unordered_map <char, std::function <std::string ()>> exits_;
    };

    class StateNotExistsException : public boost::exception, public std::exception
    {
    public:
        typedef boost::error_info <struct StateNameTag, std::string> StateName;
    };

    class UnsupportedCodeException : public boost::exception, public std::exception
    {
    public:
        typedef boost::error_info <struct CurrentStateCopyTag, State> CurrentStateCopy;
        typedef boost::error_info <struct InputCodeTag, char> InputCode;
    };

    explicit StateMachine (std::unordered_map <std::string, State> states, std::string initialStateName);
    void Consume (char code);
    const std::string &GetCurrentStateName () const;

private:
    void ValidateCurrentState () const;
    void EnterCurrentState ();

    std::unordered_map <std::string, State> states_;
    std::string currentStateName_;
};
