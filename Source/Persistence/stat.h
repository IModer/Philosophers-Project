#ifndef _STAT_
#define _STAT_

#include "../App/global.h"

#if __linux__
#include <bits/types/time_t.h>
#elif _WIN32 | _WIN64
#include <time.h>
#endif

class Stat
{
    public:

    private:
    time_t date;
    FinancialState finState;
};

#endif