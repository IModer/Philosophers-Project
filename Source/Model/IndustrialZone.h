#ifndef INDUSTRIAL_ZONE_H_DEFINED
#define INDUSTRIAL_ZONE_H_DEFINED

#include "../Persistence/Field.h"

class IndustrialZone : Field
{
    public:
    int id;
    INT_TOUPLE location;
    INT_TOUPLE size;
    //Direction direction; //ez kell?
    bool hasElectricity;
    bool isOnFire;
    bool isConnectedToRoad;
    bool isHabitable;
    int maintenanceCost;
    int workers;
    int profit;
    //int residents;
    //bool hasForest;
    //bool hasNeighbouringStadion;

    IndustrialZone(int id,
           INT_TOUPLE location,
           INT_TOUPLE size,
           int residents) : Field(id, location, size) {}

    int electricityConsumption();
};

#endif