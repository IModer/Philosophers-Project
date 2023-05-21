#include "GameField.h"


// Empty destructor
GameField::~GameField()
{

}

std::string GameField::GetDescription() {
    return Field::GetDescription() + "\n" + (hasElectricity?"Has electricity":"Doesn't have electricity") + "\n" + (isConnectedToRoad?"Is connected to a road":"Isn't connected to a road");
}

// Returns a string representation of a GameField object
std::string GameField::toString()
{
    return "";
}