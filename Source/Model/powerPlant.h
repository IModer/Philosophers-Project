#ifndef POWER_PLANT_H_DEFINED
#define POWER_PLANT_H_DEFINED
#include "GameField.h"

class PowerPlant : public GameField
{
public:
    FIELD_TYPES id;
    INT_TOUPLE location;
    INT_TOUPLE size;
    //Direction direction;  //ez kell?
    bool hasElectricity;
    bool isOnFire;
    bool isConnectedToRoad;
    bool isHabitable;
    int maintenanceCost;
    int capacity;
    static const int maxCapacity = 10; // TODO: ne 10

    PowerPlant(FIELD_TYPES id,
           INT_TOUPLE location,
           INT_TOUPLE size) : GameField(id, location, size, 10) {
            capacity = maxCapacity;
           }

    // Returns the string representation of a PowerPlant object
    std::string toString() 
    {
        return  STR(id) + " " +
                STR(location.x) + " " +
                STR(location.y) + " " +
                STR(size.x) + " " +
                STR(size.y) + " " +
                STR(hasElectricity) + " " +
                STR(isOnFire) + " " +
                STR(isConnectedToRoad) + " " +
                STR(isHabitable) + " " +
                STR(maintenanceCost) + " " +
                STR(capacity);
    }
};

#endif