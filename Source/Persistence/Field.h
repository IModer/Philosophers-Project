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
        Field(FIELD_TYPES id, INT_TOUPLE location, INT_TOUPLE size): id(id), location(location), size(size) {rect = Rectangle{static_cast<float>(location.x), static_cast<float>(location.y), static_cast<float>(size.x), static_cast<float>(size.y)}; }
        // Get, set
        FIELD_TYPES GetId() { return id;}
        int GetX()  { return location.x; }
        int GetY() { return location.y; }
        int GetWidth() { return size.x; }
        int GetHeight() { return size.y; }
        Rectangle GetRect() { return rect; }
        // Functions
        virtual std::string toString();
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
            DrawRectangleRec(rect, c); 
            };

        static Field* Factory(FIELD_TYPES id, Vector2 pos={0,0});
        static Field* Factory(FIELD_TYPES id, std::stringstream& ss);

    protected:
        // Variables
        FIELD_TYPES id;
        INT_TOUPLE location;
        INT_TOUPLE size;
        Rectangle rect;
};


#endif