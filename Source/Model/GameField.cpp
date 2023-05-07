#include "GameField.h"


// Empty destructor
GameField::~GameField()
{

}

std::string GameField::GetDescription() {
    return Field::GetDescription() + "Has elecricity: " + (hasElectricity?"true":"false") + "\nConnected To Road: " + (isConnectedToRoad?"true":"false");
}

// Returns a string representation of a GameField object
std::string GameField::toString()
{
    return "";
}