#ifndef _STAT_
#define _STAT_

#include "../App/global.h"
#include "gameObject.h"

class Stat : public GameObject
{
    public:
    // Constructor
    Stat(time_t date, finantial_state financialState);
    // Get, set
    std::string GetDate();
    // Functions
    std::string toString();

    private:
    // Variables
    time_t date; // ? kéne valami jobb
    finantial_state finState;
};

#endif