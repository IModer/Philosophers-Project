#ifndef GAME_FIED_H_DEFINED
#define GAME_FIED_H_DEFINED
#include "field.h"
#include "direction_enum.h"

class GameField : Field
{
public:
    GameField(int id,
              INT_TOUPLE location,
              INT_TOUPLE size,
              Direction dir,
              bool hasElectricity,
              bool isOnFire,
              bool isConnectedToRoad,
              bool isHabitable,
              int maintenanceCost) : Field(id, location, size),
                                     direction(dir),
                                     hasElectricity(hasElectricity),
                                     isOnFire(isOnFire),
                                     isConnectedToRoad(isConnectedToRoad),
                                     isHabitable(isHabitable),
                                     maintenanceCost(maintenanceCost) {}

    int id;
    INT_TOUPLE location;
    INT_TOUPLE size;
    Direction direction;
    bool hasElectricity;
    bool isOnFire;
    bool isConnectedToRoad;
    bool isHabitable;
    int maintenanceCost;
    std::string toString();
};

#endif