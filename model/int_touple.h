#ifndef POINT_H_DEFINED
#define POINT_H_DEFINED

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

#endif