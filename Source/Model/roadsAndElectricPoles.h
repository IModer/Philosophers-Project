#ifndef ROADS_AND_ELECTRIC_POLES_H_DEFINED
#define ROADS_AND_ELECTRIC_POLES_H_DEFINED
#include "../Persistence/Field.h"
#include "enum/direction_enum.h"


class RoadsAndElectricPoles : public Field
{
    public:
        RoadsAndElectricPoles(FIELD_TYPES id, INT_TOUPLE location, INT_TOUPLE size): Field(id,location,size) {}
        FIELD_TYPES id;
        INT_TOUPLE location;
        INT_TOUPLE size;
        int direction;
        
        // Returns the string representation of a RoadsAndElectricPoles object
        std::string toString() 
        {
            return  STR(id) + " " +
                    STR(location.x) + " " +
                    STR(location.y) + " " +
                    STR(size.x) + " " +
                    STR(size.y) + " " +
                    STR(direction);
        }

};

#endif