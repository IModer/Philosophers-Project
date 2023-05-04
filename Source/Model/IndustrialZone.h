#ifndef INDUSTRIAL_ZONE_H_DEFINED
#define INDUSTRIAL_ZONE_H_DEFINED

#include "GameField.h"

class IndustrialZone : public GameField
{
public:
    IndustrialZone(FIELD_TYPES id,
           INT_TOUPLE location,
           INT_TOUPLE size,
           int workers) : GameField(id, location, size) {}

    int electricityConsumption();

    // Returns the string representation of a IndustrialZone object
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
    bool hasNeighbouringStadion;
};

#endif