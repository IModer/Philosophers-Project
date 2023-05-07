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
    void Update() {
        age+=1/360.f;
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
    bool hasElectricity;
    bool isOnFire;
    bool isConnectedToRoad;
    bool isHabitable;
    bool hasGrownOut;
};

#endif