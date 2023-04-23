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
        _persistence.readGameState(savesPath + "base", _fields, _fin_state);   
    }
    if (savenum > numOfSaves || savenum <= 0)
    {
        //SHOULD BE UNREACHABLE
        return;
    }
    _persistence.readGameState(savesPath + "savefile" + STR(savenum) + ".sf", _fields, _fin_state);
}

void GameModel::NewGame()
{
    //Fields beállítása és beolvasás
    _fields = std::list<Field*>();
    _fields.clear();
    _fin_state = finantial_state{0,0,0,0,0};
    _fin_state.total_founds = StartingCash;
    _fin_state.loan = 0;
    _fin_state.entertainment_tax_rate,
    _fin_state.industrial_tax_rate, 
    _fin_state.residential_tax_rate = StartingTaxRate;

    //LoadGame(-1); // Alap pálya betöltése, még nem megy
    
    return;
}
// Why use Vector2 when we have INT_TOUPLE
bool GameModel::Build(FIELD_TYPES field_t, Vector2 pos) {
    //Building type alapján példányosítjuk
    auto f = Field::Factory(field_t);
    if (f == nullptr)
        return false; //Failed 
    
    //TODO
    //if (place is occupied)
    //  return false

    _fields.push_back(f); //Build the field

    //Handle the cost and other things we should
    int cost = 0;
    for (const auto [t, c] : BuildCosts)
    {
        if (t == field_t)
        {
            cost = c; break;
        }
    }
    _fin_state.total_founds -= cost; //This might not be the best way to do it, we should check if we go into debt
    
    ChechInfrastructure();  //Update the infrastructure
    //There should be a better way for this im sure 
} 