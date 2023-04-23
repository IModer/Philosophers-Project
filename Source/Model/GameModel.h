#ifndef MODEL_H_DEFINED
#define MODEL_H_DEFINED

#include <filesystem>
#include "../App/global.h"
#include "../Persistence/Persistence.h"
#include "FloatingWindow.h"
#include "enum/time_enum.h"
#include <raylib.h>

class GameModel
{
    public:
        Persistence _persistence;
        std::list<Field*> _fields;
        finantial_state _fin_state;

        int numOfSaves;
        const std::string savesPath = "./saves/";

        GameModel(Persistence* persistence) 
        {
            //numOfSaves beállítása
            //cpp 17
            numOfSaves = 0;
            for (const auto & entry : std::filesystem::directory_iterator(savesPath))
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

        void Build(Vector2 pos, int id);

        void NewGame();
        void SaveGame();
        void LoadGame(int);
        void Update() {};
        void ChechInfrastructure();
        bool Build(); //ide kell egy buildings enum
        void Demolition(INT_TOUPLE p); 
        void CauseCatastrophe();
        void ManipulateTime(TIME_ENUM t); // kell egy speed enum
        void SendFireDepartment(INT_TOUPLE p);
        void OnFieldClick(INT_TOUPLE p);

    private:
    FloatingWindow* _fWindow;

};

#endif