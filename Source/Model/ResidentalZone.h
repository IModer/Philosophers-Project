#ifndef RESIDENTAL_ZONE_H_DEFINED
#define RESIDENTAL_ZONE_H_DEFINED

#include "GameField.h"
#include <cstdlib>
#include <raylib.h>
#include <random>

class ResidentalZone : public GameField
{

public:

    ResidentalZone(FIELD_TYPES id,
           INT_TOUPLE location,
           int residents) : GameField(id, location) { this->residents = residents; }

    void Render() {
        DrawRectangleRec(rect, BROWN);
        DrawText(residents==0?"empty":STR(residents).c_str(), location.x, location.y, 24, WHITE);
    }

    void Update() {
        if (residents == 0 && rand() < 0.05) residents = maxresidents;
    }

    int electricityConsumption();

    // Returns the string representation of a ResidentalZone object
    std::string toString() 
    {
                return  STR(id) + " " +
                STR(location.x) + " " +
                STR(location.y) + " " +
                STR(hasElectricity) + " " +
                STR(isOnFire) + " " +
                STR(isConnectedToRoad) + " " +
                STR(isHabitable) + " " +
                STR(hasForest) + " " +
                STR(hasNeighbouringStadion) + " " +
                STR(residents);
    }
    
    int GetResidents() {return residents;}
    void MoveResidentsIn(int p) { residents += p; }
    void MoveResidentsOut(int p) { residents -= p; }
    int GetMaxresidents() { return  maxresidents; }

protected:
    int residents;
    int maxresidents = 10;
    bool hasElectricity;
    bool isOnFire;
    bool isConnectedToRoad;
    bool isHabitable;
    bool hasForest;
    bool hasNeighbouringStadion;
};

#endif