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
        //if (residents == 0 && isConnectedToRoad && rand() < 0.05) residents = maxresidents;
    }
    std::string GetDescription() {
        return GameField::GetDescription() + "\nResidents: " + STR(residents) + "\n has Forrest: " + (hasForest?"true":"false") + "\n Has Staidon: " + (hasStadion?"true":"false");
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
                STR(hasStadion) + " " +
                STR(residents);
    }
    void SetHasForest(bool b) {hasForest = b;}
    bool GetHasForest() {return hasForest;}

    void SetHasPolice(bool b) {hasPolice = b;}
    bool GetHasPolice() {return hasPolice;}

    void SetHasStadion(bool b) {hasStadion = b;}
    bool GetHasStadion() {return hasStadion;}
    
    int GetResidents() {return residents;}
    void MoveResidentsIn(int p) { 
        if (sourceRect.x == 0) {
            sourceRect.x += 50;
        }
        residents += p; 
    }
    void MoveResidentsOut(int p) { residents -= p; }
    int GetMaxresidents() { return  maxresidents; }

    void Upgrade() {
        if (level < 2) {
            level++;
            sourceRect.x+=50;
        }
    }

protected:
    int residents;
    int maxresidents = 10;
    int level = 0;
    bool hasForest = false;
    bool hasStadion = false;
    bool hasPolice = false;
};

#endif