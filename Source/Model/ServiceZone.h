#ifndef SERVICE_ZONE_H_DEFINED
#define SERVICE_ZONE_H_DEFINED

#include "../Persistence/Field.h"

class ServiceZone : Field
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

    ServiceZone(int id,
           INT_TOUPLE location,
           INT_TOUPLE size,
           int residents) : Field(id, location, size) {}

    int electricityConsumption();
};

#endif