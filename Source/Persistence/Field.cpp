#include "Field.h"
#include "../Model/roadsAndElectricPoles.h"
#include "../Model/forest.h"
#include "../Model/fireDepartment.h"
#include "../Model/powerPlant.h"
#include "../Model/stadion.h"
#include "../Model/residentalZone.h"
#include "../Model/ServiceZone.h"
#include "../Model/IndustrialZone.h"

std::string Field::toString()
{
    return STR(id) + " " + location.toString() + " " + size.toString();
}


//This makes Fields with a default constructor;
Field* Field::Factory(int id)
{
    Field* r;
    switch (id)
    {
    case ROADANDELECTRICPOLE:
        //Make r;
        break;
    case GAMEFIELD:
        //Make r;
        break;
    case FOREST:
        //Make r;
        break;
    case FIREDEPARTMENT:
        //Make r;
        break;
    case POWERPLANT:
        //Make r;
        break;
    case STADIUM:
        //Make r;
        break;
    case SERVICEZONE:
        //Make r;
        break;
    case INDUSTRIALZONE:
        //Make r;
        break;
    case RESIDENTALZONE:
        //Make r;
        break;
    default:
        break;
    }
    return r;
}

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
