#include "GameModel.h"
//#include "../View/View.h" // búúúúú

/**
    *   \brief Saves current gamestate
    *   Currently creates a new savefile every times its called 
    *   \return void
    **/
void GameModel::SaveGame()
{
    if (_persistence->writeGameState( savesPath + "savefile" + STR(numOfSaves) + ".sf", _fields, stat))
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
        _persistence->readGameState(savesPath + "base.sf", _fields, stat);
    }
    if (savenum > numOfSaves || savenum <= 0)
    {
        //SHOULD BE UNREACHABLE
        return;
    }
    _persistence->readGameState(savesPath + "savefile" + STR(savenum) + ".sf", _fields, stat);
}

/**
    *   \brief Set the fields of a GameObject object so that a new game can start
    *   Sets _fields, _fin_state to their default values
    * 
    *   \return void
    **/
void GameModel::NewGame()
{
    //Fields beállítása és beolvasás
    _fields = std::list<Field*>();
    _fields.clear();
    stat._time = 0;
    stat._finState = finantial_state{0,0,0,0,0};
    stat._finState.total_founds = StartingCash;
    stat._finState.loan = 0;
    stat._finState.entertainment_tax_rate,
    stat._finState.industrial_tax_rate, 
    stat._finState.residential_tax_rate = StartingTaxRate;
    speedOfTime = NORMAL;

    LoadGame(-1); // Alap pálya betöltése
    
    return;
}

// Why use Vector2 when we have INT_TOUPLE
/**
    *   \brief Tries to Build a building of type field_t to pos
    * 
    *   \param field_t The type of building to build
    *   \param pos where to build it to, should be in some [min, max]
    *   \return Whether the building was successful or not
    **/
bool GameModel::Build(FIELD_TYPES field_t, INT_TOUPLE pos) {

    //Check if pos is a valid position in _fields
    //its commented cos size in View and model are not compatible yet
        //if (checkCoordsInPlayField(pos))
            //return false; //Failed

    //Building type alapján példányosítjuk
    auto f = Field::Factory(field_t, pos);
    if (f == nullptr)
        return false; //Failed 

    _fields.push_back(f); //Build the field
    stat._finState.total_founds -= BuildCosts.at(field_t); //This might not be the best way to do it, we should check if we go into debt
    return true;

    //ChechInfrastructure();  //Update the infrastructure
} 

bool GameModel::Demolition(INT_TOUPLE pos) 
{
    //Check if pos is a valid position in _fields
    //its commented cos size in View and model are not compatible yet
    //if (checkCoordsInPlayField(pos))
    //    return false; //Failed

    //Find the building at pos and delete it
    for (Field* f : _fields)
    {
        if (f->GetX() == pos.x && f->GetY() == pos.y)
        {
            //Check for conflicting demolish

            //Is it a road 
                //Will it disconnect from the main road?
                    //If yes then resident should switch workplaces or leave the city

            //Is it a Residental Zone
                //If yes then we

            _fields.remove(f);
            //Bonus: we can give back some small money like:
            //_fin_state.total_founds -= 0.2 * BuildCosts.at(f->GetId());
            return true;  //Demolished successfully
        }
    }
    return false; //Indicate that we didnt demolish 
}

//Check if a pos is in the playing fields or not
bool GameModel::checkCoordsInPlayField(INT_TOUPLE pos)
{
    return pos.x > _fields_dim.x || pos.x < 0 || pos.y < 0 || pos.y > _fields_dim.y;
}

void GameModel::TickTock()
{
    switch (speedOfTime)
    {
    case PAUSE:
        //Nothing
        break;
    case NORMAL:
        stat._time++;
        break;
    case FAST:
        stat._time += 2;
        break;
    case FASTER:
        stat._time += 3;
        break;
    default:
        //Unreachable
        break;
    }
    //Call some AMinuteHasPassed() function where we check if we need to do something, like tax ...
}
