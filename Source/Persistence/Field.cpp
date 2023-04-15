#include "Field.h"

std::string Field::toString()
{
    return STR(id) + " " + location.toString() + " " + size.toString();
}

Field* Field::Factory(int id, std::stringstream& ss)
{
    //elágazunk az id alapján

    switch (id)
    {
    case ROADANDELECTRICPOLE:
        
        break;
    case GAMEFIELD:
        /* code */
        break;
    case FOREST:
        /* code */
        break;
    case FIREDEPARTMENT:
        /* code */
        break;
    case POWERPLANT:
        /* code */
        break;
    case STADIUM:
        /* code */
        break;
    case SERVICEZONE:
        /* code */
        break;
    case INDUSTRIALZONE:
        /* code */
        break;
    case RESIDENTZONE:
        /* code */
        break;
    default:
        //UNREACHABLE
        break;
    }

    return NULL;

}
