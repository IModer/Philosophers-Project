#ifndef ZONE_H_DEFINED
#define ZONE_H_DEFINED
#include "gameField.h"

class Zone : GameField
{

public:
    public:
    int id;
    INT_TOUPLE location;
    INT_TOUPLE size;
    Direction direction;
    bool hasElectricity;
    bool isOnFire;
    bool isConnectedToRoad;
    bool isHabitable;
    int maintenanceCost;
    int profit;
    int workers;

    Zone(int id,
           INT_TOUPLE location,
           INT_TOUPLE size) : GameField(id, location, size, 10) {} // TODO: ne 10


    int electricityConsumption();

};

#endif