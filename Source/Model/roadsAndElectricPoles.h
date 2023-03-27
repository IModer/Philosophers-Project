#ifndef ROADS_AND_ELECTRIC_POLES_H_DEFINED
#define ROADS_AND_ELECTRIC_POLES_H_DEFINED
#include "../Persistence/field.h"
#include "direction_enum.h"


class RoadsAndElectricPoles : Field
{
    public:
        RoadsAndElectricPoles(int id, INT_TOUPLE location, INT_TOUPLE size): Field(id,location,size) {}
        int id;
        INT_TOUPLE location;
        INT_TOUPLE size;
        int direction;
        std::string toString();

};

#endif