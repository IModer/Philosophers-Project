#include "GameModel.h"

void GameModel::SaveGame()
{
    _persistence.writeGameState("savefile.sf", _fields, fin_state);
}

void GameModel::LoadGame()
{
    _fields= _persistence.readGameState("savefile.sf");
}