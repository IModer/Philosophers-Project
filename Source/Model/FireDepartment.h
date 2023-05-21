#ifndef FIRE_DEPARTMENT_H_DEFINED
#define FIRE_DEPARTMENT_H_DEFINED
#include "GameField.h"
#include <raylib.h>

class FireDepartment : public GameField
{
public:


    FireDepartment(FIELD_TYPES id,
           INT_TOUPLE location) : GameField(id, location) {}

    Rectangle GetRadiusRect() {
        return Rectangle{GetX()-radius*M_UNIT/2.f+M_UNIT, GetY()-radius*M_UNIT/2.f+M_UNIT, FireDepartment::radius*M_UNIT, FireDepartment::radius*M_UNIT};
    }

    void Render() {
        DrawRectangleRec(rect, RED);
    };

    std::string GetDescription() {
        return GameField::GetDescription() + "\nFirefighters can be sent out every 20 seconds\nto extinguish fires.";
    }

    bool Update() {
        if (availableCount > 0) availableCount--;
        return false;
    }

    void SetOnFire() {}

    int getACount() {return availableCount;}
    void Use() {
        availableCount = 10; // 10 másodperc
    }

    bool InRange(Field* f) {
        return CheckCollisionRecs(GetRadiusRect(), f->GetRect());
    }

    // Returns the string representation of a FireDepartment object
    std::string toString() 
    {
        return  STR(id) + " " +
                STR(location.x) + " " +
                STR(location.y) + " " +
                STR(hasElectricity) + " " +
                STR(isOnFire) + " " +
                STR(isConnectedToRoad) + " " +
                STR(isHabitable) + " " +
                STR(hasOpenCapacity);
    }

    //virtual std::string Serialize();

    static const int radius = 20;
protected:
    bool hasOpenCapacity;
    int availableCount = 0;
};

#endif