#ifndef RESIDENTAL_ZONE_H_DEFINED
#define RESIDENTAL_ZONE_H_DEFINED
#include "gameField.h"
class ResidentalZone : GameField
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
    int residents;
    bool hasForest;
    bool hasNeighbouringStadion;

    ResidentalZone(int id,
           INT_TOUPLE location,
           INT_TOUPLE size,
           int residents) : GameField(id, location, size, 0) {}

    int electricityConsumption();
};

#endif