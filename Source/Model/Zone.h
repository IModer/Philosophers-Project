#ifndef ZONE_H_DEFINED
#define ZONE_H_DEFINED
#include "GameField.h"


//THIS IS PROBABLY NOT NEEDED
class Zone : GameField
{

public:

    Zone(FIELD_TYPES id,
           INT_TOUPLE location,
           INT_TOUPLE size) : GameField(id, location, size) {} // TODO: ne 10


    int electricityConsumption();

    std::string toString();
    
protected:
    bool hasElectricity;
    bool isOnFire;
    bool isConnectedToRoad;
    bool isHabitable;
    int profit;
    int workers;
};

#endif