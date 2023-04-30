#ifndef ZONE_H_DEFINED
#define ZONE_H_DEFINED
#include "GameField.h"

class Zone : GameField
{

public:
    FIELD_TYPES id;
    INT_TOUPLE location;
    INT_TOUPLE size;
    bool hasElectricity;
    bool isOnFire;
    bool isConnectedToRoad;
    bool isHabitable;
    int maintenanceCost;
    int profit;
    int workers;

    Zone(FIELD_TYPES id,
           INT_TOUPLE location,
           INT_TOUPLE size) : id(id), location(location), size(size), GameField(id, location, size, 10) {} // TODO: ne 10


    int electricityConsumption();

    std::string toString();

};

#endif