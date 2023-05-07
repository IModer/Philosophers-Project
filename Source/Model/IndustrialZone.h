#ifndef INDUSTRIAL_ZONE_H_DEFINED
#define INDUSTRIAL_ZONE_H_DEFINED

#include "GameField.h"
#include <raylib.h>

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
    void SetWorker(int p) {workers = p;}
    void MoveWorkerIn(int p) {workers += p;}
    void MoveWorkerOut(int p) {workers -= p;}

    int GetMaxWorkers() {return maxworkers;}

    void Render() {
        DrawRectangleRec(rect, WHITE);
    }
    std::string GetDescription() {
        return Field::GetDescription() + "\nWorkers: " + STR(workers);
    }
protected:
    int workers;
    int profit;
    int maxworkers = 10;
    bool hasNeighbouringStadion;
};

#endif