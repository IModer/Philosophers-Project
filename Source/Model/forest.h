#ifndef FOREST_H_DEFINED
#define FOREST_H_DEFINED
#include "GameField.h"

class Forest : public GameField
{
private:
    typedef GameField base;
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
                STR(hasGrownOut) + " " +
                STR(maintenanceCost) + " " +
                STR(age);
    }
};

#endif