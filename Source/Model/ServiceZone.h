#ifndef SERVICE_ZONE_H_DEFINED
#define SERVICE_ZONE_H_DEFINED

#include "GameField.h"

class ServiceZone : public GameField
{
public:
    ServiceZone(FIELD_TYPES id,
           INT_TOUPLE location,
           INT_TOUPLE size,
           int workers) : GameField(id, location, size) {}

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
                STR(workers) + " " +
                STR(profit);
    }
protected:
    int workers;
    int profit;
    //int residents;
    //bool hasForest;
    //bool hasNeighbouringStadion;
};

#endif