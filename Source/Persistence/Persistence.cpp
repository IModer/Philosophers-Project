#include "Persistence.h"
#include <iostream>
#include <fstream>

/**
    *   \brief Reads the contents of path and returns it.
    * 
    *   \param path The path to the file to write to
    *   \return List of GameObjects read from a file at path
    **/
std::list<GameObject*> Persistence::readGameState(std::string path)
{
    auto l = std::list<GameObject*>();
    //Open file at path
    //try reading from it, parse into l
    
    return l;
}

/**
    *   \brief Writes the contents of fields to path.
    *   Calls .toString() on all items of fields
    *   
    *   \warning Overwrites whatever was in path  
    * 
    *   \param path The path to the file to write to
    *   \param fields list of GameObjects to write
    *   \return True if it was successful
    **/
bool Persistence::writeGameState(std::string path, std::list<GameObject*> fields)
{
    //Open file at path
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::trunc);
    if (f.is_open())
    {
        //try writing fields to the file
        for (auto field : fields)
        {
            f << field->toString() << std::endl;
        }
    } else {
        return false; //unsuccessful
    }

    return true; //successful
}