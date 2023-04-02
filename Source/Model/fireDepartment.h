#ifndef FIRE_DEPARTMENT_H_DEFINED
#define FIRE_DEPARTMENT_H_DEFINED
#include "GameField.h"

class FireDepartment : GameField
{
public:
    int id;
    INT_TOUPLE location;
    INT_TOUPLE size;
    //Direction direction;  //ez kell?
    bool hasElectricity;
    bool isOnFire;
    bool isConnectedToRoad;
    bool isHabitable;
    int maintenanceCost;
    bool hasOpenCapacity;
    static const int radius = 10; // TODO: ne 10

    FireDepartment(int id,
           INT_TOUPLE location,
           INT_TOUPLE size,
           int maintenanceCost) : GameField(id, location, size, maintenanceCost) {}

    
};

#endif