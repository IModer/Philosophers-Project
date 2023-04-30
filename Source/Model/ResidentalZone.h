#ifndef RESIDENTAL_ZONE_H_DEFINED
#define RESIDENTAL_ZONE_H_DEFINED

#include "../Persistence/Field.h"

class ResidentalZone : public Field
{
    public:
    FIELD_TYPES id;
    INT_TOUPLE location;
    INT_TOUPLE size;
    //Direction direction; ez kell?
    bool hasElectricity;
    bool isOnFire;
    bool isConnectedToRoad;
    bool isHabitable;
    int maintenanceCost;
    int residents;
    bool hasForest;
    bool hasNeighbouringStadion;

    ResidentalZone(FIELD_TYPES id,
           INT_TOUPLE location,
           INT_TOUPLE size,
           int residents) : id(id), location(location), size(size), residents(residents), Field(id, location, size) {}

    int electricityConsumption();

    // Returns the string representation of a ResidentalZone object
    std::string toString() 
    {
                return  STR(id) + " " +
                STR(location.x) + " " +
                STR(location.y) + " " +
                STR(size.x) + " " +
                STR(size.y) + " " +
                STR(hasElectricity) + " " +
                STR(isOnFire) + " " +
                STR(isConnectedToRoad) + " " +
                STR(isHabitable) + " " +
                STR(hasForest) + " " +
                STR(hasNeighbouringStadion) + " " +
                STR(maintenanceCost) + " " +
                STR(residents);
    }
};

#endif