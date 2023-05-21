#ifndef FIRE_DEPARTMENT_H_DEFINED
#define FIRE_DEPARTMENT_H_DEFINED
#include "GameField.h"
#include <raylib.h>

class FireDepartment : public GameField
{
public:


    FireDepartment(FIELD_TYPES id,
           INT_TOUPLE location) : GameField(id, location) {}

    void Render() {
        DrawRectangleRec(rect, RED);
    };
    // Returns the string representation of a FireDepartment object
    std::string toString() 
    {
        return  STR(id) + " " +
                STR(location.x) + " " +
                STR(location.y) + " " +
                STR(hasElectricity) + " " +
                STR(isOnFire) + " " +
                STR(isConnectedToRoad) + " " +
                STR(isHabitable) + " " +
                STR(hasOpenCapacity);
    }

    //virtual std::string Serialize();

    static const int radius = 20; // TODO: ne 10
protected:
    bool hasOpenCapacity;
};

#endif