#ifndef INDUSTRIAL_ZONE_H_DEFINED
#define INDUSTRIAL_ZONE_H_DEFINED

#include "GameField.h"

class IndustrialZone : public GameField
{
public:
    IndustrialZone(FIELD_TYPES id,
           INT_TOUPLE location,
           int workers) : GameField(id, location) {}

    int electricityConsumption();

    // Returns the string representation of a IndustrialZone object
    std::string toString() 
    {
        return  STR(id) + " " +
                STR(location.x) + " " +
                STR(location.y) + " " +
                STR(hasElectricity) + " " +
                STR(isOnFire) + " " +
                STR(isConnectedToRoad) + " " +
                STR(isHabitable) + " " +
                STR(workers) + " " +
                STR(profit);
    }

    //getter/setter
    int GetProfit() {return profit;}
    void SetProfit(int p) {profit = p;}
    int GetWorkers() {return workers;}
    void SetWorkers(int p) {workers = p;}
protected:
    int workers;
    int profit;
    bool hasNeighbouringStadion;
};

#endif