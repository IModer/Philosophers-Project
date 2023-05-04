#ifndef POLICE_STATION_H_DEFINED
#define POLICE_STATION_H_DEFINED
#include "GameField.h"

class PoliceStation : public GameField
{
    public:
    FIELD_TYPES id;
    INT_TOUPLE location;
    INT_TOUPLE size;
    //Direction direction; //ez kell?
    bool hasElectricity;
    bool isOnFire;
    bool isConnectedToRoad;
    bool isHabitable;
    int maintenanceCost;
    //static const int radius = 10; // TODO: ne 10

    PoliceStation(FIELD_TYPES id,
           INT_TOUPLE location,
           INT_TOUPLE size) : GameField(id, location, size, 10), id(id), location(location), size(size) {}

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