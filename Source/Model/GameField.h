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
    virtual bool Update() {
        if (isOnFire) {
            if (beenOnFire++ > 15 && rand()%100 < 20) return true;
        }else if (rand()%100 < 10) SetOnFire();
        return false;
    }
    bool HasElectricity() { return hasElectricity; };
    bool IsOnFire() { return isOnFire; }
    void SetOnFire() { isOnFire = true; }
    void Extinguish() { isOnFire = false; beenOnFire = 0; }
    std::string toString();
    
    //getterek/setterek ide
    bool GetIsConnectedToRoad() {return isConnectedToRoad;}
    void SetIsConnectedToRoad(bool b) {isConnectedToRoad = b;}

    bool GetHasElectricity() {return hasElectricity;}
    void SetHasElectricity(bool b) {hasElectricity = b;}

protected: 
    int beenOnFire = 0;
    bool hasElectricity = false;
    bool isOnFire = false;
    bool isConnectedToRoad = false;
    bool isHabitable = true;
};

#endif