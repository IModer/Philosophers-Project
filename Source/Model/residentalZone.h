#ifndef RESIDENTAL_ZONE_H_DEFINED
#define RESIDENTAL_ZONE_H_DEFINED

#include "../Persistence/Field.h"

class ResidentalZone : Field
{
    public:
    int id;
    INT_TOUPLE location;
    INT_TOUPLE size;
    //Direction direction; ez kell?
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
           int residents) : Field(id, location, size) {}

    int electricityConsumption();
};

#endif