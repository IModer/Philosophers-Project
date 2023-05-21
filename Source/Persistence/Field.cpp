#include "Field.h"
#include "../Model/RoadsAndElectricPoles.h"
#include "../Model/Forest.h"
#include "../Model/FireDepartment.h"
#include "../Model/PowerPlant.h"
#include "../Model/Stadion.h"
#include "../Model/ResidentalZone.h"
#include "../Model/ServiceZone.h"
#include "../Model/IndustrialZone.h"
#include "../Model/PoliceStation.h"
#include <raylib.h>

Texture2D Field::images;

// Returns the string representation of a Fields object
std::string Field::toString()
{
    return STR(id) + " " + location.toString()  + " " + STR(BuildingSizes.at(this->GetId()).x) + " " + STR(BuildingSizes.at(this->GetId()).y);
}

std::string Field::GetDescription() {
    return BuildingNames.at(id) + "\n" + "Position: " + STR(location.x) + " " + STR(location.y);
}

std::string Field::Serialize()
{
    return STR(id) + " " + location.toString();
}

//The everything is 0 behaviour should be changed
/**
    *   \brief Creates a subclass of Fields based on id
    * 
    *   \param id Should FIELD_TYPES
    *   \warning Some fields of the return Object might not be initialized
    *   \warning All other fields are 0
    *   \return A Field subclass object with default values
    **/
Field* Field::Factory(FIELD_TYPES id, INT_TOUPLE pos)
{
    Field* r;
    switch (id)
    {
    case ROADANDELECTRICPOLE:
        r = new RoadsAndElectricPoles(id, V2_TO_IT(pos));
        break;
    case GAMEFIELD:
        r = new GameField(id, V2_TO_IT(pos));
        break;
    case FOREST:
        r = new Forest(id, V2_TO_IT(pos));
        break;
    case FIREDEPARTMENT:
        r = new FireDepartment(id, V2_TO_IT(pos));
        break;
    case POWERPLANT:
        r = new PowerPlant(id, V2_TO_IT(pos));
        break;
    case STADIUM:
        r = new Stadion(id, V2_TO_IT(pos));
        break;
    case SERVICEZONE:
        r = new ServiceZone(id, V2_TO_IT(pos), 0);
        break;
    case INDUSTRIALZONE:
        r = new IndustrialZone(id, V2_TO_IT(pos),0);
        break;
    case RESIDENTALZONE:
        r = new ResidentalZone(id, V2_TO_IT(pos), 0);
        break;
    case POLICESTATION:
        r = new PoliceStation(id, V2_TO_IT(pos));
    default:
        break;
        //Should be unreadable
    }
    return r;
}

/**
    *   \brief Creates a subclass of Fields based on id and with attributes read from ss
    * 
    *   \param id Should FIELD_TYPES
    *   \param ss The values to be read from
    *   \return A Field subclass object with values read from ss
    **/
Field* Field::Factory(FIELD_TYPES id, std::stringstream& ss)
{
    Field* r;
    int age, workers, residents;
    INT_TOUPLE location;
 
    ss >> location.x >> location.y;
    
    //elágazunk az id alapján
    switch (id)
    {
        case ROADANDELECTRICPOLE:
            {
                RoadsAndElectricPoles* a = new RoadsAndElectricPoles(id, location);
                r = a;
                break;
            }
        case GAMEFIELD:
            break;
        case FOREST:
            {
                ss >> age;
                auto b = new Forest(id, location);
                b->SetAge(age);
                r = b;
                break;
            }
        case FIREDEPARTMENT:
            {
                auto c = new FireDepartment(id, location);
                r = c;
                break;
            }
        case POWERPLANT:
            {
                auto d = new PowerPlant(id, location);
                r = d;
                break;
            }
        case STADIUM:
            {
                auto e = new Stadion(id, location);
                r = e;
                break;
            }
        case SERVICEZONE:
            {
                ss >> workers;
                auto f = new ServiceZone(id, location, workers);
                r = f;
                break;
            }
        case INDUSTRIALZONE:
            {
                ss >> workers;
                auto g = new IndustrialZone(id, location, workers);
                r = g;
                break;
            }
        case RESIDENTALZONE:
            {
                ss >> residents;
                auto i = new ResidentalZone(id, location, residents);
                r = i;
                break;
            }
        default:
            //UNREACHABLE
            break;
    }

    return r;

}
