#ifndef FOREST_H_DEFINED
#define FOREST_H_DEFINED
#include "GameField.h"

class Forest : GameField
{

public:
    int id;
    INT_TOUPLE location;
    INT_TOUPLE size;
    //Direction direction; //ez kell?
    bool hasElectricity;
    bool isOnFire;
    bool isConnectedToRoad;
    bool isHabitable;
    int maintenanceCost;
    int age;
    bool hasGrownOut;

    Forest(int id,
           INT_TOUPLE location,
           INT_TOUPLE size,
           int age) : GameField(id, location, size, 10),
                               age(age) 
                               {
                                hasGrownOut = false;
                               }
};

#endif