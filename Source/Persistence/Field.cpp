#include "Field.h"

std::string Field::toString()
{
    return STR(id) + " " + location.toString() + " " + size.toString();
}