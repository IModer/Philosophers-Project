#ifndef PERSISTANCE_H_DEFINED
#define PERSISTANCE_H_DEFINED

#include "GameObject.h"
#include "Stat.h"
#include "Field.h"
#include <list>

class IOException : std::exception
{
    private: 
        std::string _w;
    public:
        IOException(std::string w): _w(w) {}

        std::string what()
        {
            return _w;
        }
};

class Persistence
{
public:
    void readGameState(std::string path, std::list<Field*>& fields, Stat& stat);
    bool writeGameState(std::string path, std::list<Field*> fields, Stat stat);
};

#endif