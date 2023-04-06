#include "Field.h"

std::string Field::toString()
{
    return STR(id) + " " + location.toString() + " " + size.toString();
}

Field* Field::Factory(int id, std::stringstream& ss)
{
    //elágazunk az id alapján
    auto a = 1 + 2;
    return NULL;

}
