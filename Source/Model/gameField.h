#ifndef GAME_FIED_H_DEFINED
#define GAME_FIED_H_DEFINED
#include "../Persistence/field.h"
#include "direction_enum.h"

class GameField : Field
{
public:
    GameField(int id,
              INT_TOUPLE location,
              INT_TOUPLE size,
              int maintenanceCost) : Field(id, location, size),
                                     maintenanceCost(maintenanceCost) {}

    GameField(Field field) : Field(field) {};

    int id;
    INT_TOUPLE location;
    INT_TOUPLE size;
    bool hasElectricity;
    bool isOnFire;
    bool isConnectedToRoad;
    bool isHabitable;
    int maintenanceCost;
    std::string toString();
};

#endif