#ifndef MODEL_H_DEFINED
#define MODEL_H_DEFINED

#include <filesystem>
#include <tuple>
#include "../App/global.h"
#include "../Persistence/Persistence.h"
#include "FloatingWindow.h"
#include "enum/time_enum.h"

using namespace std;

class GameModel
{
    public:
        Persistence _persistence;
        list<Field*> _fields;
        finantial_state _fin_state;

        int numOfSaves;
        const string savesPath = "./saves/";

        //Gameplay variables
        const int StartingCash = 10000;
        const int StartingTaxRate = 10;

        //This can be tweaked any time to balace the game, maybe it can even scale with time or money spent, ect...
        //Scaleing wouldnt be that hard, int scale = x; 50*scale, 100*scale ...
        const list<tuple<FIELD_TYPES,int>> BuildCosts = {
            {ROADANDELECTRICPOLE,    50},
            {FOREST,                100},
            {FIREDEPARTMENT,       1000},
            {POWERPLANT,           2000},
            {STADIUM,              4000},
            {SERVICEZONE,          2000},
            {INDUSTRIALZONE,       3000},
            {RESIDENTALZONE,       1000}
        };

        GameModel(Persistence* persistence) 
        {
            //numOfSaves beállítása
            //cpp 17
            numOfSaves = 0;
            for (const auto & entry : filesystem::directory_iterator(savesPath))
            {
                if (entry.path().extension() == ".sf")
                {
                    numOfSaves++;
                }
            }
            printf("DEBUG: numOfSaves = %i\n", numOfSaves);
        };

        void OpenFWindow() 
        {
            if(_fWindow != nullptr)
            {
                delete _fWindow;
            } 
            _fWindow = new FloatingWindow(nullptr); 
        }; //TODO ne nullptr 
        FloatingWindow* GetFWindow() { return _fWindow; }
        void CloseFWindow() { delete _fWindow; _fWindow = nullptr; }
        void NewGame();
        void SaveGame();
        void LoadGame(int);
        void Update() {};
        void ChechInfrastructure();
        bool Build(FIELD_TYPES field_t, Vector2 pos); //ide kell egy buildings enum
        void Demolition(INT_TOUPLE p); 
        void CauseCatastrophe();
        void ManipulateTime(TIME_ENUM t); // kell egy speed enum
        void SendFireDepartment(INT_TOUPLE p);
        void OnFieldClick(INT_TOUPLE p);

    private:
    FloatingWindow* _fWindow;

};

#endif