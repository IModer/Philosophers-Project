#ifndef GAME_FIED_H_DEFINED
#define GAME_FIED_H_DEFINED
#include "../Persistence/Field.h"
#include "enum/direction_enum.h"

class GameField : public Field
{
public:
    GameField(FIELD_TYPES id,
              INT_TOUPLE location) : Field(id, location) {}

    GameField(Field field) : Field(field) {};
    ~GameField();
    virtual std::string GetDescription();
    bool HasElectricity() { return hasElectricity; };
    std::string toString();
    
    //getterek/setterek ide
    bool GetIsConnectedToRoad() {return isConnectedToRoad;}
    void SetIsConnectedToRoad(bool b) {isConnectedToRoad = b;}

    bool GetHasElectricity() {return hasElectricity;}
    void SetHasElectricity(bool b) {hasElectricity = b;}

protected: 
    bool hasElectricity = false;
    bool isOnFire = false;
    bool isConnectedToRoad = false;
    bool isHabitable = true;
};

#endif