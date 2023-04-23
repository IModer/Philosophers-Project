#ifndef FOREST_H_DEFINED
#define FOREST_H_DEFINED
#include "GameField.h"

class Forest : public GameField
{
private:
    typedef GameField base;
public:
    Forest(FIELD_TYPES id,
           INT_TOUPLE location,
           INT_TOUPLE size,
           int age) : GameField(id, location, size, 10), age(age) { }

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
                STR(maintenanceCost) + " " +
                STR(age);
    }
protected:
    static const int grownAge = 10;
    int age;
};

#endif