#ifndef _GLOBAL_
#define _GLOBAL_

#include "raylib.h"

#include <string>
#include <vector>

class INT_TOUPLE{
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
};


typedef struct {
    // stuff
} FinancialState;


#endif