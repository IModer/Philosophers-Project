#ifndef FOREST_H_DEFINED
#define FOREST_H_DEFINED
#include "gameField.h"

class Forest : GameField
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
    int age;
    bool hasGrownOut;

    Forest(int id,
           INT_TOUPLE location,
           INT_TOUPLE size,
           Direction dir,
           bool hasElectricity,
           bool isOnFire,
           bool isConnectedToRoad,
           bool isHabitable,
           int maintenanceCost,
           int age,
           bool hasGrownOut) : GameField(id, location, size, dir, hasElectricity, isOnFire, isConnectedToRoad, isHabitable, maintenanceCost),
                               age(age), hasGrownOut(hasGrownOut) {}
};

#endif