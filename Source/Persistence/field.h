#ifndef FIELD_H_DEFINED
#define FIELD_H_DEFINED

#include "../App/global.h"
#include "gameObject.h"
#include <raylib.h>


class Field : public GameObject
{
    public:
        // Constructor
        Field(int id, INT_TOUPLE location, INT_TOUPLE size): id(id), location(location), size(size) {}
        // Get, set
        int GetX()  { return location.x; }
        int GetY() { return location.y; }
        // INT_TOUPLE GetPos(); // ha kell
        int GetWidth() { return size.x; }
        int GetHeight() { return size.y; }
        // Functions
        std::string toString();
        void Render();
    
    protected:
        // Variables
        int id;
        INT_TOUPLE location;
        INT_TOUPLE size;
};


#endif