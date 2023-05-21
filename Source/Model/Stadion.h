#ifndef STADION_H_DEFINED
#define STADION_H_DEFINED
#include "GameField.h"
#include <raylib.h>

class Stadion : public GameField
{
public:
    static const int radius = 10; // TODO: ne 10

    Stadion(FIELD_TYPES id,
           INT_TOUPLE location) : GameField(id, location) {}

    void Render() {
        DrawRectangleRec(rect, DARKBLUE);
    }

    //virtual std::string Serialize();

    // Returns the string representation of a Stadion object
    std::string toString() 
    {
        return  STR(id) + " " +
                STR(location.x) + " " +
                STR(location.y) + " " +
                STR(hasElectricity) + " " +
                STR(isOnFire) + " " +
                STR(isConnectedToRoad) + " " +
                STR(isHabitable);
    }
};

#endif