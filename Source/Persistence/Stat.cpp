#include "Stat.h"

std::string Stat::toString()
{
    return "stat";
}

Stat::Stat(time_t date, finantial_state financialState)
{
    _date = date;
    _finState = financialState;
}

Stat::~Stat() 
{

}