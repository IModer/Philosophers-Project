#ifndef FOREST_H_DEFINED
#define FOREST_H_DEFINED
#include "GameField.h"
#include <raylib.h>

class Forest : public GameField
{
public:

    Forest(FIELD_TYPES id,
           INT_TOUPLE location) : GameField(id, location)
                               {
                                hasGrownOut = false;
                                age = 0;
                               }
    void Render() override {
        DrawRectangleRec(rect, GREEN);
        DrawText(STR((int)(age)).c_str(), location.x, location.y, 24, WHITE);
    }
    bool Update() override {
        if (age < 1)
        {
            age+=1/360.f;
        } else {
            hasGrownOut = true;
        }
        return GameField::Update();
    }

    std::string GetDescription() override {
        return GameField::GetDescription() + "\nA forest that needs 10 years to grow out.\nIncreases nearby happiness.";
    }

    void SetAge(int i)
    {
        age = i;
    }

    // Returns the string representation of a Forest object
    std::string toString() override
    {
        return  STR(id) + " " +
                STR(location.x) + " " +
                STR(location.y) + " " +
                STR(hasElectricity) + " " +
                STR(isOnFire) + " " +
                STR(isConnectedToRoad) + " " +
                STR(isHabitable) + " " +
                STR(hasGrownOut) + " " +
                STR(age);
    }

    std::string Serialize() override
    {
        return STR(id) + " " + location.toString() + " " + STR(age);
    } 

protected:
    double age;
    bool hasGrownOut;
};

#endif