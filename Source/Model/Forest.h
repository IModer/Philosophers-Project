#ifndef FOREST_H_DEFINED
#define FOREST_H_DEFINED
#include "GameField.h"

class Forest : public GameField
{
public:

    Forest(FIELD_TYPES id,
           INT_TOUPLE location,
           INT_TOUPLE size) : GameField(id, location, size)
                               {
                                hasGrownOut = false;
                               }

    // Returns the string representation of a Forest object
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
                STR(age);
    }
protected:
    int age;
    bool hasElectricity;
    bool isOnFire;
    bool isConnectedToRoad;
    bool isHabitable;
    bool hasGrownOut;
};

#endif