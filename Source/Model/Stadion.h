#ifndef STADION_H_DEFINED
#define STADION_H_DEFINED
#include "GameField.h"

class Stadion : public GameField
{
public:
    static const int radius = 10; // TODO: ne 10

    Stadion(FIELD_TYPES id,
           INT_TOUPLE location) : GameField(id, location) {}


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