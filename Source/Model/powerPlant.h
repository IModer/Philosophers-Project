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
    static const int maxCapacity = 10; // TODO: ne 10

    PowerPlant(int id,
           INT_TOUPLE location,
           INT_TOUPLE size) : GameField(id, location, size, 10) {
            capacity = maxCapacity;
           }
};

#endif