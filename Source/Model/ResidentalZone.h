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

    void Render() override {
        DrawRectangleRec(rect, BROWN);
        DrawText(residents==0?"empty":STR(residents).c_str(), location.x, location.y, 24, WHITE);
    }
    std::string GetDescription() override {
        return GameField::GetDescription() + "\nResidents: " + STR(residents) + "\n" + (level==0?"Basic housing. Can accomodate 10 people.":(level==1?"A big house. Can accomodate 20 people.":"A luxurius apartment complex.\nCan accomodate 40 people."));
    }

    int electricityConsumption();

    // Returns the string representation of a ResidentalZone object
    std::string toString() override
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

    std::string Serialize() override
    {
        return STR(id) + " " + location.toString() + " " +STR(residents);
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
            maxresidents*=2;
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