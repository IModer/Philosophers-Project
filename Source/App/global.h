#ifndef _GLOBAL_
#define _GLOBAL_

#include "raylib.h"

#include <string>
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

const int FPS = 60;

typedef struct INT_TOUPLE { // ? szerintem sruct erre jobban illik
    int x, y;
    std::string toString() {
        return STR(x) + " " + STR(y);
    }
} INT_TOUPLE;

/* class INT_TOUPLE{
>>>>>>> Source/App/global.h
    private:
        int _x;
        int _y;

    public: 
        INT_TOUPLE()
        {
            this->_x = 0;
            this->_y = 0;
        }
        INT_TOUPLE(int x, int y) : _x(x), _y(y) {}
        int getX() const { return _x; }
        int getY() const { return _y; }
}; */



typedef enum { MENU = 0, GAME } GAME_STATE;

struct finantial_state
{
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
};

#endif