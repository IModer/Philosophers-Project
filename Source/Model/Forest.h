#ifndef FOREST_H_DEFINED
#define FOREST_H_DEFINED
#include "GameField.h"
#include <raylib.h>

class Forest : public GameField
{
public:

    Forest(FIELD_TYPES id,
           INT_TOUPLE location) : GameField(id, location)
                               {
                                hasGrownOut = false;
                               }
    void Render() {
        DrawRectangleRec(rect, GREEN);
        DrawText(STR((int)(age)).c_str(), location.x, location.y, 24, WHITE);
    }
    bool Update() {
        age+=1/360.f;
        return false;
    }

    // Returns the string representation of a Forest object
    std::string toString() 
    {
        return  STR(id) + " " +
                STR(location.x) + " " +
                STR(location.y) + " " +
                STR(hasElectricity) + " " +
                STR(isOnFire) + " " +
                STR(isConnectedToRoad) + " " +
                STR(isHabitable) + " " +
                STR(hasGrownOut) + " " +
                STR(age);
    }
protected:
    double age;
    bool hasGrownOut;
};

#endif