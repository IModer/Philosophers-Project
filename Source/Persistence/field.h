#ifndef FIELD_H_DEFINED
#define FIELD_H_DEFINED

#include "../App/global.h"
#include "gameObject.h"


class Field : public GameObject
{
    public:
        Field(int id, INT_TOUPLE location, INT_TOUPLE size): id(id), location(location), size(size) {}
        std::string toString();

        void Render();
    
    protected:
        int id;
        INT_TOUPLE location;
        INT_TOUPLE size;
};


#endif