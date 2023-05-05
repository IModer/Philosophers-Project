#ifndef POLICE_STATION_H_DEFINED
#define POLICE_STATION_H_DEFINED
#include "GameField.h"

class PoliceStation : public GameField
{
public:

    PoliceStation(FIELD_TYPES id,
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

protected:
    bool hasElectricity;
    bool isOnFire;
    bool isConnectedToRoad;
    bool isHabitable;
    static const int radius = 10; // TODO: ne 10
};

#endif