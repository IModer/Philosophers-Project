#ifndef GAME_FIED_H_DEFINED
#define GAME_FIED_H_DEFINED
#include "../Persistence/Field.h"
#include "enum/direction_enum.h"

class GameField : public Field
{
public:
    GameField(int id,
              INT_TOUPLE location,
              INT_TOUPLE size,
              int maintenanceCost) : Field(id, location, size),
                                     maintenanceCost(maintenanceCost) {}

    GameField(Field field) : Field(field) {};
    ~GameField();
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