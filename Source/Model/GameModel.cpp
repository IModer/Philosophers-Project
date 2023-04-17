#include "GameModel.h"

/**
    *   \brief Saves current gamestate
    *   Currently creates a new savefile every times its called 
    *   \return void
    **/
void GameModel::SaveGame()
{
    if (_persistence.writeGameState( savesPath + "savefile" + STR(numOfSaves) + ".sf", _fields, _fin_state))
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
    if (savenum == -1)
    {
        _fields= _persistence.readGameState(savesPath + "base");   
    }
    if (savenum > numOfSaves || savenum <= 0)
    {
        //SHOULD BE UNREACHABLE
        return;
    }
    _fields= _persistence.readGameState(savesPath + "savefile" + STR(savenum) + ".sf");
}

void GameModel::NewGame()
{
    //Fields beállítása és beolvasás
    _fields = new std::list<Field*>;
    _fin_state = finantial_state{0,0,0,0,0};
    //LoadGame(-1); // Alap pálya betöltése
    
    return;
}

void GameModel::Build(Vector2 pos, int id) {
    for(Field* f : _fields)
    {
        if(f->GetX() == pos.x && f->GetY() == pos.y)
        {
            printf("There was an overlap\n");
            if (id < 0) {
                _fields.remove(f);
            }
            return;
        }
    }
    if (id >= 0)
    _fields.push_back(new Field(id, INT_TOUPLE{static_cast<int>(pos.x), static_cast<int>(pos.y)}, INT_TOUPLE{50, 50})); // factoryval?
} 