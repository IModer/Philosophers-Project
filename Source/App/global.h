#ifndef _GLOBAL_
#define _GLOBAL_

#include "raylib.h"

#include <string>
//this might be bad
#include <sstream>
#include <vector>

#ifdef debug
#include <iostream>
#endif

#if __linux__
#include <bits/types/time_t.h>

#elif _WIN32 | _WIN64
#include <time.h>

#endif

#define STR(x) std::to_string(x)

//Ids for Field types
typedef enum {
    ROADANDELECTRICPOLE = 1,
    GAMEFIELD = 2,
    FOREST = 3,
    FIREDEPARTMENT = 4,
    POWERPLANT = 5,
    STADIUM = 6,
    SERVICEZONE = 7,
    INDUSTRIALZONE = 8,
    RESIDENTALZONE = 9
} FIELD_TYPES;

const int FPS = 60;

typedef struct INT_TOUPLE { 
    int x, y;
    std::string toString() {
        return STR(x) + " " + STR(y);
    }
} INT_TOUPLE;

typedef enum { MENU = 0, GAME } GAME_STATE;

struct finantial_state
{
#include <istream>
    //lehet egy class update methoddal ahol a rezidensek száma szerint pénzt szed be és adót fizet ki?
    //will see
    int total_founds;
    int loan;
    //lehet float is és akkor százalék
    int residential_tax_rate;
    int industrial_tax_rate;
    int entertainment_tax_rate;
    //this change is purely experimental

    std::string toString() {
        return STR(total_founds) + " " + STR(loan) + " " + STR(residential_tax_rate) + " " + STR(industrial_tax_rate) + " " + STR(entertainment_tax_rate);
    }
    
    friend std::ostream & operator<<(std::ostream& is, finantial_state& f)
    {
        is  <<  f.total_founds            << " " <<
                f.loan                    << " " << 
                f.residential_tax_rate    << " " <<
                f.industrial_tax_rate     << " " <<
                f.entertainment_tax_rate  << " " << std::endl;
        return is;
    }

    friend std::ostream & operator>>(std::stringstream& is, finantial_state& f)
    {
        //TODO Handle error
        std::string s_total_founds; std::string s_loan; std::string s_residential_tax_rate;
        std::string s_industrial_tax_rate; std::string s_entertainment_tax_rate;
        is >> s_total_founds >> s_loan >> s_residential_tax_rate >> s_industrial_tax_rate >> s_entertainment_tax_rate;

        f.total_founds = std::stoi(s_total_founds);
        f.loan = std::stoi(s_loan);
        f.residential_tax_rate = std::stoi(s_residential_tax_rate);
        f.industrial_tax_rate = std::stoi(s_industrial_tax_rate);
        f.entertainment_tax_rate = std::stoi(s_entertainment_tax_rate);
        
        return is;
    }
};

#endif