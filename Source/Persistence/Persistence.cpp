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
    *   \param &fields list of Fields to read to
    *   \param &fin_state FinantialState to read to
    *   \throw IOException
    *   \return void
    **/
void Persistence::readGameState(std::string path, std::list<Field*>& fields, Stat& stat) //TODO
{
    //printf("Reading Game State\n");

    auto l = std::list<Field*>(); Stat s;
    time_t d; finantial_state fS;
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

        ss >> d; ss >> fS;
        s = Stat(d, fS);

        //std::cout << "DEBUG d : " << d << " fS : " << fS.toString() << std::endl;
        
        //Fieldek beolvasása
        while (std::getline(f, line))
        {
            //Reset ss
            ss.str("");
            ss.clear();
            ss << line;
            int id;
            ss >> id;

            //std::cout << "DEBUG id: " << id << std::endl;

            //példányosítani
            auto a = Field::Factory(static_cast<FIELD_TYPES>(id), ss);
            
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
        //std::cout << "DEBUG: " << BuildingNames.at(x->GetId()) << " = " << x->toString() << std::endl;
        fields.push_back(x);
    }

    //Set stat
    stat = s;
}

/**
    *   \brief Writes the contents of fields to path.
    *   Calls .toString() on all items of fields
    *   
    *   \warning Overwrites whatever was in path  
    * 
    *   \param path The path to the file to write to
    *   \param fields List of Fields to write
    *   \param fin_state FinantialState to write
    *   \return Indicated whether the write was successful or not
    **/
bool Persistence::writeGameState(std::string path, std::list<Field*> fields, Stat stat)
{
    //Open file at path
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::trunc);
    if (f.is_open())
    {
        //write the time
        f << stat._time << " ";
        //write financial struct
        f << stat._finState;  //nem kell endl mert a _finState kiírja
        //writing fields to the file
        for (auto field : (fields))
        {
            f << field->Serialize() << std::endl;
        }
    } else {
        return false; //unsuccessful
    }

    f.close();
    return true; //successful
}