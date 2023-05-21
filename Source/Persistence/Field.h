#ifndef FIELD_H_DEFINED
#define FIELD_H_DEFINED

#include "../App/global.h"
#include "GameObject.h"
#include <raylib.h>
#include <sstream>

class Field : public GameObject
{
    public:
        static Texture2D images;
        // Constructor
        Field(FIELD_TYPES id, INT_TOUPLE location): id(id), location(location)
        {
            rect = Rectangle{
                static_cast<float>(location.x),
                static_cast<float>(location.y),
                static_cast<float>(GetWidth()),
                static_cast<float>(GetHeight())
                };
            sourceRect = SourceRects.at(id);
        }
        // Get, set
        FIELD_TYPES GetId() { return id;}
        int GetX()  { return location.x; }
        int GetY() { return location.y; }
        INT_TOUPLE GetPos() { return location; }
        int GetWidth() { return BuildingSizes.at(this->GetId()).x*M_UNIT; }
        int GetHeight() { return BuildingSizes.at(this->GetId()).y*M_UNIT; }
        Rectangle GetRect() { return rect; }
        Rectangle GetDrawRect() {
            int w = BuildingSizes.at(GetId()).y;
            return Rectangle{rect.x, rect.y-10*w, rect.width, rect.height+10*w};
        }
        Rectangle GetSourceRect() {
            return sourceRect;
        }
        virtual std::string GetDescription();
        // Functions
        virtual std::string toString();
        virtual std::string Serialize();
        virtual void Render() { 
            /*Color c;
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
            DrawRectangleRec(rect, c); */
        };
        virtual bool Update() { return false; };

        static Field* Factory(FIELD_TYPES id, INT_TOUPLE pos={0,0});
        static Field* Factory(FIELD_TYPES id, std::stringstream& ss);
    protected:
        // Variables
        FIELD_TYPES id;
        INT_TOUPLE location;
        INT_TOUPLE size;
        Rectangle rect;
        Rectangle sourceRect;
};


#endif