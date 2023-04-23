#include "Field.h"
#include "../Model/roadsAndElectricPoles.h"
#include "../Model/forest.h"
#include "../Model/fireDepartment.h"
#include "../Model/powerPlant.h"
#include "../Model/stadion.h"
#include "../Model/residentalZone.h"
#include "../Model/ServiceZone.h"
#include "../Model/IndustrialZone.h"

// Returns the srting representation of a Fields object
std::string Field::toString()
{
    return STR(id) + " " + location.toString() + " " + size.toString();
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
Field* Field::Factory(int id)
{
    Field* r;
    switch (id)
    {
    case ROADANDELECTRICPOLE:
        r = new RoadsAndElectricPoles(id, INT_TOUPLE{0,0}, INT_TOUPLE{0,0});
        break;
    case GAMEFIELD:
        r = new GameField(id, INT_TOUPLE{0,0}, INT_TOUPLE{0,0}, 0);
        break;
    case FOREST:
        r = new Forest(id, INT_TOUPLE{0,0}, INT_TOUPLE{0,0}, 0);
        break;
    case FIREDEPARTMENT:
        r = new FireDepartment(id, INT_TOUPLE{0,0}, INT_TOUPLE{0,0}, 0);
        break;
    case POWERPLANT:
        r = new PowerPlant(id, INT_TOUPLE{0,0}, INT_TOUPLE{0,0});
        break;
    case STADIUM:
        r = new Stadion(id, INT_TOUPLE{0,0}, INT_TOUPLE{0,0});
        break;
    case SERVICEZONE:
        r = new ServiceZone(id, INT_TOUPLE{0,0}, INT_TOUPLE{0,0}, 0);
        break;
    case INDUSTRIALZONE:
        r = new IndustrialZone(id, INT_TOUPLE{0,0}, INT_TOUPLE{0,0}, 0);
        break;
    case RESIDENTALZONE:
        r = new ResidentalZone(id, INT_TOUPLE{0,0}, INT_TOUPLE{0,0}, 0);
        break;
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
Field* Field::Factory(int id, std::stringstream& ss)
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
            RoadsAndElectricPoles* a = new RoadsAndElectricPoles(id, location, size);
            a->direction = direction;
            r = a;
            break;
        }
    case GAMEFIELD:
        //

        break;
    case FOREST:
        {
            ss >> location.x >> location.y >> size.x >> size.y >> hasElectricity >> isOnFire >> isConnectedToRoad >> isHabitable >> hasGrownOut >> maintenanceCost >> age;
            auto b = new Forest(id, location, size, age);
            b->hasElectricity = hasElectricity;
            b->isOnFire = isOnFire;
            b->isConnectedToRoad = isConnectedToRoad;
            b->isHabitable = isHabitable;
            b->hasGrownOut = hasGrownOut;
            b->maintenanceCost = maintenanceCost;
            r = b;
            break;
        }
    case FIREDEPARTMENT:
        {
            ss >> location.x >> location.y >> size.x >> size.y >> hasElectricity >> isOnFire >> isConnectedToRoad >> isHabitable >> hasOpenCapacity >> maintenanceCost;
            auto c = new FireDepartment(id, location, size, maintenanceCost);
            c->hasElectricity = hasElectricity;
            c->isOnFire = isOnFire;
            c->isConnectedToRoad = isConnectedToRoad;
            c->isHabitable = isHabitable;
            c->hasOpenCapacity = hasOpenCapacity;
            r = c;
            break;
        }
    case POWERPLANT:
        {
            ss >> location.x >> location.y >> size.x >> size.y >> hasElectricity >> isOnFire >> isConnectedToRoad >> isHabitable >> maintenanceCost >> capacity;
            auto d = new PowerPlant(id, location, size);
            d->hasElectricity = hasElectricity;
            d->isOnFire = isOnFire;
            d->isConnectedToRoad = isConnectedToRoad;
            d->isHabitable = isHabitable;
            d->maintenanceCost = maintenanceCost;
            d->capacity = capacity;
            r = d;
            break;
        }
    case STADIUM:
        {
            ss >> location.x >> location.y >> size.x >> size.y >> hasElectricity >> isOnFire >> isConnectedToRoad >> isHabitable >> maintenanceCost;
            auto e = new Stadion(id, location, size);
            e->hasElectricity = hasElectricity;
            e->isOnFire = isOnFire;
            e->isConnectedToRoad = isConnectedToRoad;
            e->isHabitable = isHabitable;
            e->maintenanceCost = maintenanceCost;
            r = e;
            break;
        }
    case SERVICEZONE:
        {
            ss >> location.x >> location.y >> size.x >> size.y >> hasElectricity >> isOnFire >> isConnectedToRoad >> isHabitable >> maintenanceCost >> workers >> profit;
            auto f = new ServiceZone(id, location, size, 0);  //???
            f->hasElectricity = hasElectricity;
            f->isOnFire = isOnFire;
            f->isConnectedToRoad = isConnectedToRoad;
            f->isHabitable = isHabitable;
            f->maintenanceCost = maintenanceCost;
            f->workers = workers;
            f->profit = profit;
            r = f;
            break;
        }
    case INDUSTRIALZONE:
        {
            ss >> location.x >> location.y >> size.x >> size.y >> hasElectricity >> isOnFire >> isConnectedToRoad >> isHabitable >> maintenanceCost >> workers >> profit;
            auto g = new IndustrialZone(id, location, size, 0);  //???
            g->hasElectricity = hasElectricity;
            g->isOnFire = isOnFire;
            g->isConnectedToRoad = isConnectedToRoad;
            g->isHabitable = isHabitable;
            g->maintenanceCost = maintenanceCost;
            g->workers = workers;
            g->profit = profit;
            r = g;
            break;
        }
    case RESIDENTALZONE:
        {
            ss >> location.x >> location.y >> size.x >> size.y >> hasElectricity >> isOnFire >> isConnectedToRoad >> isHabitable >> hasForest >> hasNeighbouringStadion >> maintenanceCost >> residents;
            auto i = new ResidentalZone(id, location, size, residents);  //???
            i->hasElectricity = hasElectricity;
            i->isOnFire = isOnFire;
            i->isConnectedToRoad = isConnectedToRoad;
            i->isHabitable = isHabitable;
            i->hasForest = hasForest;
            i->hasNeighbouringStadion = hasNeighbouringStadion;
            i->maintenanceCost = maintenanceCost;
            r = i;
            break;
        }
    default:
        //UNREACHABLE
        break;
    }

    return r;

}
