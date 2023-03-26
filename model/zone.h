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
           INT_TOUPLE size,
           Direction dir,
           bool hasElectricity,
           bool isOnFire,
           bool isConnectedToRoad,
           bool isHabitable,
           int maintenanceCost,
           int profit,
           int workers) : GameField(id, location, size, dir, hasElectricity, isOnFire, isConnectedToRoad, isHabitable, maintenanceCost),
                               profit(profit), workers(workers) {}


    int electricityConsumption();

};

#endif