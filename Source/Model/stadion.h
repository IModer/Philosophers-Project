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
    static const int radius = 10; // TODO: ne 10

    Stadion(int id,
           INT_TOUPLE location,
           INT_TOUPLE size) : GameField(id, location, size, 10) {}
};

#endif