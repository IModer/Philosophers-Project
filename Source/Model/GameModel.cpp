#include "GameModel.h"

void GameModel::NewGame()
{
    //Fields beállítása és beolvasás
    _fields = new std::list<Field*>;
    LoadGame(-1); // Alap pálya betöltése
    
    return;
}