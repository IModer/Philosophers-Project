#include "Persistence.h"
#include "Field.h"
#include "Stat.h"
#include <iostream>
#include <fstream>
#include <sstream>

/**
    *   \brief Reads the contents of path and returns it.
    * 
    *   \param path The path to the file to write to
    *   \throw IOException
    *   \return List of GameObjects read from a file at path
    **/
void Persistence::readGameState(std::string path, std::list<Field*>& fields, finantial_state& fin_state) //TODO
{
    auto l = std::list<Field*>();
    //Open file at path
    std::ifstream f;
    f.open(path, std::ios::in);
    //try reading from it, parse into l
    if (f.is_open())
    {
        //Statok kiolvasása
        std::string line;
        std::stringstream ss;

        std::getline(f, line);
        ss << line;

        time_t d; finantial_state fS;
        ss >> d; ss >> fS;
        Stat* s = new Stat(d, fS); 

        //Fieldek beolvasása
        while (std::getline(f, line))
        {
            ss << line;
            int id;
            ss >> id;

            //példányosítani
            auto a = Field::Factory(id, ss);
            
            //hozzáadni a listához
            l.push_back(a);  
        }
        
    } else 
    {
        throw IOException("Failed to open file!");
    }

    //Copy l -> fields
    //TODO CHECK IF READING IN WAS SUCCESSFUL
    fields.clear();
    for (auto x : l)
    {
        fields.push_back(x);
    }
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
bool Persistence::writeGameState(std::string path, std::list<Field*> fields, finantial_state fin_state)
{
    //Open file at path
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::trunc);
    if (f.is_open())
    {
        //write financial struct
        f << fin_state << std::endl;
        //writing fields to the file
        for (auto field : (fields))
        {
            f << field->toString() << std::endl;
        }
    } else {
        return false; //unsuccessful
    }

    f.close();
    return true; //successful
}