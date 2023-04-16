#ifndef MODEL_H_DEFINED
#define MODEL_H_DEFINED

#include "../App/global.h"
#include "../Persistence/Persistence.h"
#include "FloatingWindow.h"
#include "enum/time_enum.h"

class GameModel
{
    public:
        Persistence _persistence;
        std::list<Field*> _fields;

        GameModel(Persistence* persistence) {};

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
        void LoadGame();
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