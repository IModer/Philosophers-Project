#include "GameModel.h"
#include "IndustrialZone.h"
#include "ServiceZone.h"
#include "ResidentalZone.h"
#include "Zone.h"

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
    stat._finState = finantial_state();
    stat._finState.total_founds = StartingCash;
    stat._finState.loan = 0;
    stat._finState.SetIndustrialTaxRate(StartingTaxRate);
    stat._finState.SetServiceTaxRate(StartingTaxRate);
    stat._finState.SetResidentialTaxRate(StartingTaxRate);
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

void GameModel::Causality()
{
    stat._time++;   //Move time by one unit
    Update();       //Check if we need to do thing 
}

//View should call this every time it want time to move
void GameModel::TickTock()
{
    switch (speedOfTime)
    {
    case PAUSE:
        //Nothing
        break;
    case NORMAL:
        Causality();
        break;
    case FAST:
        Causality();Causality();
        break;
    case FASTER:
        Causality();Causality();Causality();
        break;
    default:
        //Unreachable
        break;
    }
}

void GameModel::ManipulateTime(TIME_ENUM t)
{
    //WE probably dont need any checks
    speedOfTime = t;
}

//Is called every gametick by Causality
//Handles: tax
//         [here be more thing]
void GameModel::Update()
{
    //Tax

    //We tax every month
    auto ONE_MONTH_IN_TICKS = 1; //Choose a number
    if (stat._time % ONE_MONTH_IN_TICKS == 0)
    {
        //Go through every field, tax according to the num of residents/workers
        auto tax = 0;
        for (auto f : _fields)
        {
            switch ((FIELD_TYPES)f->GetId())
            {
            case INDUSTRIALZONE:
                //tax += dynamic_cast<IndustrialZone*>(f)->workers * stat._finState.GetIndustrialTaxRate();
                break;
            case SERVICEZONE:
                //tax += dynamic_cast<ServiceZone*>(f)->workers * stat._finState.GetServiceTaxRate();
                break;
            case RESIDENTALZONE:
                //tax += dynamic_cast<ResidentalZone*>(f)->residents * stat._finState.GetResidentialTaxRate();
                break;
            default:
                //Unreachable
                break;
            }
        }
        stat._finState.total_founds -= tax;
    }
}