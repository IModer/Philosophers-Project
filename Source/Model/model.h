#ifndef MODEL_H_DEFINED
#define MODEL_H_DEFINED
#include "persistence.h"
#include "int_touple.h"
#include "time_enum.h"

class Model
{
    public:
        Persistence _persistence;
        std::list<GameObject> _fields;

        void NewGame();
        void SaveGame();
        void LoadGame();
        void Update();
        void ChechInfrastructure();
        bool Build(); //ide kell egy buildings enum
        void Demolition(INT_TOUPLE p); 
        void CauseCatastrophe();
        void ManipulateTime(TIME_ENUM t); // kell egy speed enum
        void SendFireDepartment(INT_TOUPLE p);
        void OnFieldClick(INT_TOUPLE p);
};

#endif