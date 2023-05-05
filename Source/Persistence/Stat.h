#ifndef _STAT_
#define _STAT_

#include "../App/global.h"
#include "GameObject.h"

class Stat : public GameObject
{
    public:
    // Constructor
    Stat() {};
    Stat(time_t time, finantial_state financialState);
    ~Stat();
    void TickTock();
    // Get, set
    std::string GetDate();  //fancy getter?
    // Functions
    std::string toString();

    time_t _time;
    finantial_state _finState;
};

#endif