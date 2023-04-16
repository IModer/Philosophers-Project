#include "GameModel.h"

/**
    *   \brief Saves current gamestate
    *   Currently creates a new savefile every times its called 
    *   \return void
    **/
void GameModel::SaveGame()
{
    if (_persistence.writeGameState( savesPath + "savefile" + STR(numOfSaves) + ".sf", _fields, fin_state))
        numOfSaves++;
}

//Maybe SaveNewGame and SaveExistingGame
//Egyik új fájlba ment, a másik felülr egy létezőt 

/**
    *   \brief Loads in a saved gamestate
    * 
    *   \param savenum which save to load in, should be in [1, numOfSaves]
    *   \return void
    **/
void GameModel::LoadGame(int savenum)
{
    if (savenum > numOfSaves || savenum <= 0)
    {
        //SHOULD BE UNREACHABLE
        return;
    }
    _fields= _persistence.readGameState("savefile.sf");
}

void GameModel::NewGame()
{
    //Fields beállítása és beolvasás
    _fields = new std::list<Field*>;
    LoadGame(-1); // Alap pálya betöltése
    
    return;
}