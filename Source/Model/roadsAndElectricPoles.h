#ifndef ROADS_AND_ELECTRIC_POLES_H_DEFINED
#define ROADS_AND_ELECTRIC_POLES_H_DEFINED
#include "../Persistence/Field.h"
#include "enum/direction_enum.h"


class RoadsAndElectricPoles : public Field
{
    public:
        RoadsAndElectricPoles(int id, INT_TOUPLE location, INT_TOUPLE size): Field(id,location,size) {}
        int id;
        INT_TOUPLE location;
        INT_TOUPLE size;
        int direction;
        
        std::string toString() 
        {
            return  STR(id) + " " +
                    STR(location.x) + " " +
                    STR(location.y) + " " +
                    STR(size.x) + " " +
                    STR(size.y);
        }

};

#endif