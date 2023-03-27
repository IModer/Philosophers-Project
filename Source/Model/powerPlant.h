#ifndef POWER_PLANT_H_DEFINED
#define POWER_PLANT_H_DEFINED
#include "gameField.h"

class PowerPlant : GameField
{
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
    int capacity;

    PowerPlant(int id,
           INT_TOUPLE location,
           INT_TOUPLE size,
           Direction dir,
           bool hasElectricity,
           bool isOnFire,
           bool isConnectedToRoad,
           bool isHabitable,
           int maintenanceCost,
           int capacity) : GameField(id, location, size, dir, hasElectricity, isOnFire, isConnectedToRoad, isHabitable, maintenanceCost),
                               capacity(capacity) {}
};

#endif