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
        Persistence* _persistence;
        list<Field*> _fields;
        finantial_state _fin_state;

        int numOfSaves;
        const string savesPath = "./saves/";

        //Gameplay variables
        const int StartingCash = 10000;
        const int StartingTaxRate = 10;

        GameModel(Persistence* persistence) 
        {
            //Init _persistance ans _fields
            _persistence = persistence;
            _fields = list<Field*>();
            _fin_state = finantial_state{0,0,0,0,0};

            //numOfSaves beállítása
            numOfSaves = 0;
            for (const auto & entry : filesystem::directory_iterator(savesPath))
            {
                if (entry.path().extension() == ".sf")
                {
                    numOfSaves++;
                }
            }

            //Init FloatingWindow
            _fWindow = nullptr;
        };

        void OpenFWindow(Field* f) 
        {
            if(_fWindow != nullptr)
            {
                delete _fWindow;
            } 
            _fWindow = new FloatingWindow(f); 
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