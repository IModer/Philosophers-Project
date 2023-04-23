#ifndef STADION_H_DEFINED
#define STADION_H_DEFINED
#include "GameField.h"

class Stadion : public GameField
{
public:
    static const int radius = 10; // TODO: ne 10

    Stadion(FIELD_TYPES id,
           INT_TOUPLE location,
           INT_TOUPLE size) : GameField(id, location, size, 10) {}


    // Returns the string representation of a Stadion object
    std::string toString() 
    {
        return  STR(id) + " " +
                STR(location.x) + " " +
                STR(location.y) + " " +
                STR(size.x) + " " +
                STR(size.y) + " " +
                STR(hasElectricity) + " " +
                STR(isOnFire) + " " +
                STR(isConnectedToRoad) + " " +
                STR(isHabitable) + " " +
                STR(maintenanceCost);
    }
};

#endif