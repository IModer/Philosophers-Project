#ifndef GAME_FIED_H_DEFINED
#define GAME_FIED_H_DEFINED
#include "../Persistence/Field.h"
#include "enum/direction_enum.h"

class GameField : public Field
{
public:
    GameField(FIELD_TYPES id,
              INT_TOUPLE location,
              INT_TOUPLE size,
              int maintenanceCost) : id(id), location(location), size(size), Field(id, location, size),
                                     maintenanceCost(maintenanceCost) {}

    GameField(Field field) : Field(field) {};
    ~GameField();
    std::string toString();
    protected: 
    bool hasElectricity;
    bool isOnFire;
    bool isConnectedToRoad;
    bool isHabitable;
    int maintenanceCost;
};

#endif