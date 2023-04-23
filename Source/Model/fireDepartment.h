#ifndef FIRE_DEPARTMENT_H_DEFINED
#define FIRE_DEPARTMENT_H_DEFINED
#include "GameField.h"

class FireDepartment : public GameField
{
public:
    static const int radius = 10; // TODO: ne 10

    FireDepartment(FIELD_TYPES id,
           INT_TOUPLE location,
           INT_TOUPLE size,
           int maintenanceCost) : GameField(id, location, size, maintenanceCost) {}

    // Returns the string representation of a FireDepartment object
    std::string toString() 
    {
        return  location.toString();/*STR(id) + " " +
                STR(location.x) + " " +
                STR(location.y) + " " +
                STR(size.x) + " " +
                STR(size.y) + " " +
                STR(hasElectricity) + " " +
                STR(isOnFire) + " " +
                STR(isConnectedToRoad) + " " +
                STR(isHabitable) + " " +
                STR(hasOpenCapacity) + " " +
                STR(maintenanceCost);*/
    }
    protected:
    bool hasOpenCapacity;

};

#endif