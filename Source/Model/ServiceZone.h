#ifndef SERVICE_ZONE_H_DEFINED
#define SERVICE_ZONE_H_DEFINED

#include "GameField.h"

class ServiceZone : public GameField
{
public:
    ServiceZone(FIELD_TYPES id,
           INT_TOUPLE location,
           int workers) : GameField(id, location) {}

    int electricityConsumption();

    // Returns the string representation of a ServiceZone object
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
    void SetWorker(int p) {workers = p;}
    
    int GetMaxWorkers() {return maxworkers;}

protected:
    int workers;
    int profit;
    int maxworkers = 10;
    //int residents;
    //bool hasForest;
    //bool hasNeighbouringStadion;
};

#endif