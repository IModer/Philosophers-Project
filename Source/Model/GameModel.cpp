#include "GameModel.h"
#include "../View/View.h" // búúúúú

/**
    *   \brief Saves current gamestate
    *   Currently creates a new savefile every times its called 
    *   \return void
    **/
void GameModel::SaveGame()
{
    if (_persistence->writeGameState( savesPath + "savefile" + STR(numOfSaves) + ".sf", _fields, _fin_state))
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
        _persistence->readGameState(savesPath + "base", _fields, _fin_state);   
    }
    if (savenum > numOfSaves || savenum <= 0)
    {
        //SHOULD BE UNREACHABLE
        return;
    }
    _persistence->readGameState(savesPath + "savefile" + STR(savenum) + ".sf", _fields, _fin_state);
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
/**
    *   \brief Tries to Build a building of type field_t to pos
    * 
    *   \param field_t The type of building to build
    *   \param pos where to build it to, should be in some [min, max]
    *   \return Whether the building was successful or not
    **/
bool GameModel::Build(FIELD_TYPES field_t, INT_TOUPLE pos) {
    //Building type alapján példányosítjuk
    auto f = Field::Factory(field_t, pos);
    if (f == nullptr)
        return false; //Failed 

    //Check if pos is a valid position in _fields
    if (pos.x > _fields_dim.x/2*M_UNIT || pos.x < _fields_dim.x/-2*M_UNIT || pos.y < _fields_dim.y/-2*M_UNIT || pos.y > (_fields_dim.y/2)*M_UNIT ) {
        std::cout << "oh shet\n";
        return false; //Failed
    }

    _fields.push_back(f); //Build the field
    _fin_state.total_founds -= BuildCosts.at(field_t); //This might not be the best way to do it, we should check if we go into debt
    return true;

    //ChechInfrastructure();  //Update the infrastructure
} 

bool GameModel::Demolition(INT_TOUPLE pos) 
{
    //Check if pos is a valid position in _fields
    if (pos.x > _fields_dim.x || pos.x < 0 || pos.y < 0 || pos.y > _fields_dim.y )
        return false; //Failed
    //Find the buildinf at pos and delete it
    for (Field* f : _fields)
    {
        if (f->GetX() == pos.x && f->GetY() == pos.y)
        {
            _fields.remove(f);
            //TODO: Some check should go here
            return true;  //Demolished successfully
        }
    }
    return false; //Indicate that we didnt demolish 
}