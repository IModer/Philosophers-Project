#ifndef RESIDENTAL_ZONE_H_DEFINED
#define RESIDENTAL_ZONE_H_DEFINED

#include "GameField.h"

class ResidentalZone : public GameField
{

public:

    ResidentalZone(FIELD_TYPES id,
           INT_TOUPLE location,
           int residents) : GameField(id, location) {}

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
    void MoveResidentsOut(int p) {residents -= p; }
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