#ifndef FIRE_DEPARTMENT_H_DEFINED
#define FIRE_DEPARTMENT_H_DEFINED
#include "GameField.h"

class FireDepartment : public GameField
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
    int maintenanceCost;  // Lehet ezt is ki lehet emelni LUT-ba
    bool hasOpenCapacity;
    static const int radius = 10; // TODO: ne 10

    FireDepartment(FIELD_TYPES id,
           INT_TOUPLE location,
           INT_TOUPLE size,
           int maintenanceCost) : id(id), location(location), size(size), maintenanceCost(maintenanceCost), GameField(id, location, size, maintenanceCost) {}

    // Returns the string representation of a FireDepartment object
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
                STR(hasOpenCapacity) + " " +
                STR(maintenanceCost);
    }
};

#endif