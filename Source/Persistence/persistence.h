#ifndef PERSISTANCE_H_DEFINED
#define PERSISTANCE_H_DEFINED

#include "gameObject.h"
#include <list>

class Persistence
{
public:
    std::list<GameObject> readGameState(std::string path);
    bool writeGameState(std::string path, std::list<GameObject> fields);
};

#endif