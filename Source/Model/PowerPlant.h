#ifndef POWER_PLANT_H_DEFINED
#define POWER_PLANT_H_DEFINED
#include "GameField.h"

class PowerPlant : public GameField
{
public:
    PowerPlant(FIELD_TYPES id,
           INT_TOUPLE location) : GameField(id, location) {
            capacity = maxCapacity;
           }

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
protected:
    int capacity;
    static const int maxCapacity = 10; // TODO: ne 10
};

#endif