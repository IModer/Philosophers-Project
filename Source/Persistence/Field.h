#ifndef FIELD_H_DEFINED
#define FIELD_H_DEFINED

#include "../App/global.h"
#include "GameObject.h"
#include <raylib.h>
#include <sstream>

class Field : public GameObject
{
    public:
        // Constructor
        Field(int id, INT_TOUPLE location, INT_TOUPLE size): id(id), location(location), size(size) {}
        // Get, set
        int GetId() { return id;}
        int GetX()  { return location.x; }
        int GetY() { return location.y; }
        // INT_TOUPLE GetPos(); // ha kell 
        int GetWidth() { return size.x; }
        int GetHeight() { return size.y; }
        // Functions
        std::string toString();
        void Render() { 
            Color c;
            switch (id) {
                case ROADANDELECTRICPOLE:
                c = GRAY;
                break;
                case GAMEFIELD:
                c = WHITE;
                break;
                case FOREST:
                c = GREEN;
                break;
                case FIREDEPARTMENT:
                c = RED;
                break;
                default:
                c = BLUE;
                break;
            }
            DrawRectangleRec(Rectangle{static_cast<float>(location.x), static_cast<float>(location.y), static_cast<float>(size.x), static_cast<float>(size.y)}, c); 
            };

        static Field* Factory(int id, std::stringstream& ss);

    protected:
        // Variables
        int id;
        INT_TOUPLE location;
        INT_TOUPLE size;
};


#endif