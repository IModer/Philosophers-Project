#ifndef ROADS_AND_ELECTRIC_POLES_H_DEFINED
#define ROADS_AND_ELECTRIC_POLES_H_DEFINED
#include "field.h"
#include "direction_enum.h"


class RoadsAndElectricPoles : Field
{
    public:
        RoadsAndElectricPoles(int id, INT_TOUPLE location, INT_TOUPLE size, Direction dir): Field(id,location,size), direction(dir) {}
        int id;
        INT_TOUPLE location;
        INT_TOUPLE size;
        Direction direction;
        std::string toString();

};

#endif