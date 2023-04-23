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
    std::list<Field*> readGameState(std::string path);
    bool writeGameState(std::string path, std::list<Field*> fields, finantial_state fin_state);
};

#endif