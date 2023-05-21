#ifndef ZONE_H_DEFINED
#define ZONE_H_DEFINED
#include "GameField.h"


//THIS IS PROBABLY NOT NEEDED
class Zone : GameField
{

public:

    Zone(FIELD_TYPES id,
           INT_TOUPLE location) : GameField(id, location) {}


    int electricityConsumption();

    std::string toString();

    //virtual std::string Serialize();
    
protected:
    int profit;
    int workers;
};

#endif