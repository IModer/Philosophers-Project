#include "Stat.h"

std::string Stat::toString()
{
    return "stat";
}

Stat::Stat(time_t time, finantial_state financialState)
{
    _time = time;
    _finState = financialState;
}

Stat::~Stat() 
{

}