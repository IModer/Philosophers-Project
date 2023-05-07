#ifndef ROADS_AND_ELECTRIC_POLES_H_DEFINED
#define ROADS_AND_ELECTRIC_POLES_H_DEFINED
#include "GameField.h"
#include "enum/direction_enum.h"
#include <raylib.h>


class RoadsAndElectricPoles : public GameField
{
public:
    RoadsAndElectricPoles(FIELD_TYPES id, INT_TOUPLE location): GameField(id,location) {}
        
    void Render() {
        DrawRectangleRec(rect, GRAY);
    }
    
    // Returns the string representation of a RoadsAndElectricPoles object
    std::string toString() 
    {
        return  STR(id) + " " +
                STR(location.x) + " " +
                STR(location.y) + " " +
                STR(direction);
    }
protected:
    bool hasElectricity = false;
    int direction;
};

#endif