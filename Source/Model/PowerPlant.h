#ifndef POWER_PLANT_H_DEFINED
#define POWER_PLANT_H_DEFINED
#include "GameField.h"
#include <raylib.h>

class PowerPlant : public GameField
{
public:
    PowerPlant(FIELD_TYPES id,
           INT_TOUPLE location) : GameField(id, location) {
            //capacity = maxCapacity;
            hasElectricity = true;
           }

    void Render() {
        DrawRectangleRec(rect, YELLOW);
    }

    std::string GetDescription() {
        return GameField::GetDescription() + "\nCapacity: " + STR(capacity);
    }

    //virtual std::string Serialize();

    // Returns the string representation of a PowerPlant object
    std::string toString() 
    {
        return  STR(id) + " " +
                STR(location.x) + " " +
                STR(location.y) + " " +
                STR(hasElectricity) + " " +
                STR(isOnFire) + " " +
                STR(isConnectedToRoad) + " " +
                STR(isHabitable) + " " +
                STR(capacity);
    }

    int GetCapacity() {return capacity;}
    void SetCapacity(int p) {capacity = p;}
protected:
    int capacity = 10;
    bool hasElectricity = true;
    //static const int maxCapacity = 10;
};

#endif