#ifndef STADION_H_DEFINED
#define STADION_H_DEFINED
#include "gameField.h"

class Stadion : GameField
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
    int radius;

    Stadion(int id,
           INT_TOUPLE location,
           INT_TOUPLE size,
           Direction dir,
           bool hasElectricity,
           bool isOnFire,
           bool isConnectedToRoad,
           bool isHabitable,
           int maintenanceCost,
           bool hasOpenCapacity,
           int radius) : GameField(id, location, size, dir, hasElectricity, isOnFire, isConnectedToRoad, isHabitable, maintenanceCost),
                               radius(radius) {}
};

#endif