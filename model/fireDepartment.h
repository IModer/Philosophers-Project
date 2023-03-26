#ifndef FIRE_DEPARTMENT_H_DEFINED
#define FIRE_DEPARTMENT_H_DEFINED
#include "gameField.h"

class FireDepartment : GameField
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
    bool hasOpenCapacity;
    int radius;

    FireDepartment(int id,
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
                               hasOpenCapacity(hasOpenCapacity), radius(radius) {}
};

#endif