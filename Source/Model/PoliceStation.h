#ifndef POLICE_STATION_H_DEFINED
#define POLICE_STATION_H_DEFINED
#include "GameField.h"
#include <raylib.h>

class PoliceStation : public GameField
{
public:

    PoliceStation(FIELD_TYPES id,
           INT_TOUPLE location) : GameField(id, location) {}

    void Render() {
        DrawRectangleRec(rect, BLUE);
    }
    std::string GetDescription() {
        return GameField::GetDescription() + "\nA police station to stop crime.\nIncreases happiness.";
    }

    // Returns the string representation of a Stadion object
    std::string toString() 
    {
        return  STR(id) + " " +
                STR(location.x) + " " +
                STR(location.y) + " " +
                STR(hasElectricity) + " " +
                STR(isOnFire) + " " +
                STR(isConnectedToRoad) + " " +
                STR(isHabitable);
    }

    //virtual std::string Serialize();

protected:
    static const int radius = 10; // TODO: ne 10
};

#endif