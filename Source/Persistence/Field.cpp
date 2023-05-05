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

// Returns the string representation of a Fields object
std::string Field::toString()
{
    return STR(id) + " " + location.toString()  + " " + STR(BuildingSizes.at(this->GetId()).x) + " " + STR(BuildingSizes.at(this->GetId()).y);
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
    //elágazunk az id alapján
    Field* r;
    int direction, maintenanceCost, age, capacity, workers, profit, residents;
    INT_TOUPLE location, size;
    bool hasElectricity, isOnFire, isConnectedToRoad, isHabitable, hasGrownOut, hasOpenCapacity, hasForest, hasNeighbouringStadion;
    switch (id)
    {
    case ROADANDELECTRICPOLE:
        {
            ss >> location.x >> location.y >> size.x >> size.y >> direction;
            RoadsAndElectricPoles* a = new RoadsAndElectricPoles(id, location);
            // a->direction = direction; // checkInfrastructure dolga
            r = a;
            break;
        }
    case GAMEFIELD:
        //

        break;
    case FOREST:
        {
            ss >> location.x >> location.y >> size.x >> size.y >> hasElectricity >> isOnFire >> isConnectedToRoad >> isHabitable >> hasGrownOut >> maintenanceCost >> age;
            auto b = new Forest(id, location);
            //set age
            // b->hasElectricity = hasElectricity; // checkInfrastructure dolga
            // b->isOnFire = isOnFire;
            // b->isConnectedToRoad = isConnectedToRoad;
            // b->isHabitable = isHabitable;
            // b->hasGrownOut = hasGrownOut;
            // b->maintenanceCost = maintenanceCost;
            r = b;
            break;
        }
    case FIREDEPARTMENT:
        {
            ss >> location.x >> location.y >> size.x >> size.y >> hasElectricity >> isOnFire >> isConnectedToRoad >> isHabitable >> hasOpenCapacity;
            auto c = new FireDepartment(id, location);
            /*c->hasElectricity = hasElectricity; // checkInfrastructure dolga
            c->isOnFire = isOnFire;
            c->isConnectedToRoad = isConnectedToRoad;
            c->isHabitable = isHabitable;
            c->hasOpenCapacity = hasOpenCapacity; */
            r = c;
            break;
        }
    case POWERPLANT:
        {
            ss >> location.x >> location.y >> size.x >> size.y >> hasElectricity >> isOnFire >> isConnectedToRoad >> isHabitable >> capacity;
            auto d = new PowerPlant(id, location);
            // d->hasElectricity = hasElectricity;
            // d->isOnFire = isOnFire;
            // d->isConnectedToRoad = isConnectedToRoad;
            // d->isHabitable = isHabitable;
            // d->capacity = capacity;
            r = d;
            break;
        }
    case STADIUM:
        {
            ss >> location.x >> location.y >> size.x >> size.y >> hasElectricity >> isOnFire >> isConnectedToRoad >> isHabitable;
            auto e = new Stadion(id, location);
            // e->hasElectricity = hasElectricity;
            // e->isOnFire = isOnFire;
            // e->isConnectedToRoad = isConnectedToRoad;
            // e->isHabitable = isHabitable;
            r = e;
            break;
        }
    case SERVICEZONE:
        {
            ss >> location.x >> location.y >> size.x >> size.y >> hasElectricity >> isOnFire >> isConnectedToRoad >> isHabitable >> workers >> profit;
            auto f = new ServiceZone(id, location, workers);  //TODO
            // f->hasElectricity = hasElectricity;
            // f->isOnFire = isOnFire;
            // f->isConnectedToRoad = isConnectedToRoad;
            // f->isHabitable = isHabitable;
            // f->workers = workers;
            // f->profit = profit;
            r = f;
            break;
        }
    case INDUSTRIALZONE:
        {
            ss >> location.x >> location.y >> size.x >> size.y >> hasElectricity >> isOnFire >> isConnectedToRoad >> isHabitable >> workers >> profit;
            auto g = new IndustrialZone(id, location, workers);  //TODO
            // g->hasElectricity = hasElectricity;
            // g->isOnFire = isOnFire;
            // g->isConnectedToRoad = isConnectedToRoad;
            // g->isHabitable = isHabitable;
            // g->workers = workers;
            // g->profit = profit;
            r = g;
            break;
        }
    case RESIDENTALZONE:
        {
            ss >> location.x >> location.y >> size.x >> size.y >> hasElectricity >> isOnFire >> isConnectedToRoad >> isHabitable >> hasForest >> hasNeighbouringStadion >> residents;
            auto i = new ResidentalZone(id, location, residents);  //TODO
            // i->hasElectricity = hasElectricity;
            // i->isOnFire = isOnFire;
            // i->isConnectedToRoad = isConnectedToRoad;
            // i->isHabitable = isHabitable;
            // i->hasForest = hasForest;
            // i->hasNeighbouringStadion = hasNeighbouringStadion;
            r = i;
            break;
        }
    default:
        //UNREACHABLE
        break;
    }

    return r;

}
