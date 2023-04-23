#ifndef SERVICE_ZONE_H_DEFINED
#define SERVICE_ZONE_H_DEFINED

#include "../Persistence/Field.h"

class ServiceZone : public Field
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

    // Returns the string representation of a ServiceZone object
    std::string toString() 
    {
        return  STR(id) + " " +
                STR(location.x) + " " +
                STR(location.y) + " " +
                STR(size.x) + " " +
                STR(size.y) + " " +
                STR(hasElectricity) + " " +
                STR(isOnFire) + " " +
                STR(isConnectedToRoad) + " " +
                STR(isHabitable) + " " +
                STR(maintenanceCost) + " " +
                STR(workers) + " " +
                STR(profit);
    }
};

#endif