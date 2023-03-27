#ifndef FIELD_H_DEFINED
#define FIELD_H_DEFINED

#include "../App/global.h"
#include "gameObject.h"


class Field : public GameObject
{
    public:
        Field(int id, INT_TOUPLE location, INT_TOUPLE size): id(id), location(location), size(size) {}
        int id;
        INT_TOUPLE location;
        INT_TOUPLE size;
        std::string toString();
    
    //lehet "privatizálni a metódusokat ha úgy van"
    private:

        //a pegazus előtt semmi sem privát

};


#endif