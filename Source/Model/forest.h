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
           int age) : GameField(id, location, size, 10),
                               age(age) {
                                // TODO: set hasGrownOut
                               }
};

#endif