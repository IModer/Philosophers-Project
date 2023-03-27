#ifndef FIELD_H_DEFINED
#define FIELD_H_DEFINED

#include "gameObject.h"
#include "int_touple.h"


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

};


#endif