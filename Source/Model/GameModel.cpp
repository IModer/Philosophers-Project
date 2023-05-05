#include "GameModel.h"
#include "IndustrialZone.h"
#include "ServiceZone.h"
#include "ResidentalZone.h"
#include "Zone.h"
#include <raylib.h>

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
    satisfaction = 10; //idk
    Gameover = false;

    // LoadGame(-1); // Alap pálya betöltése
    
    return;
}

// Why use Vector2 when we have INT_TOUPLE
/**
    *   \brief Tries to Build a building of type field_t to pos
    * 
    *   \param field_t The type of building to build
    *   \param pos where to build it to, should be in some [min, max]
    *   \return Whether the buil_fin_stateding was successful or not
    **/
bool GameModel::Build(FIELD_TYPES field_t, INT_TOUPLE pos) {
    if (!Gameover)
    {
        //Building type alapján példányosítjuk
        auto f = Field::Factory(field_t, pos);
        if (f == nullptr)
        {
            printf("DEBUG");
            return false; //Failed 
        }

        //Check if pos is a valid position in _fields
        if (pos.x > _fields_dim.x/2*M_UNIT || pos.x < _fields_dim.x/-2*M_UNIT || pos.y < _fields_dim.y/-2*M_UNIT || pos.y > (_fields_dim.y/2)*M_UNIT ) {
            delete f;
            return false; //Failed
        }

        // Check all other buildings
        for(Field* i : _fields) {
            if (CheckCollisionRecs(f->GetRect(), i->GetRect())) {
                delete f;
                return false;
            }
        }

        _fields.push_back(f); //Build the field
        stat._finState.total_founds -= BuildCosts.at(field_t); //This might not be the best way to do it, we should check if we go into debt
        return true;

        //ChechInfrastructure();  //Update the infrastructure
    }
} 

bool GameModel::Demolition(INT_TOUPLE pos) 
{
    if (!Gameover)
    {
        //Check if pos is a valid position in _fields
        //its commented cos size in View and model are not compatible yet
        //if (checkCoordsInPlayField(pos))
        //    return false; //Failed

        //Find the building at pos and delete it
        for (Field* f : _fields)
        {
            if (CheckCollisionPointRec(IT_TO_V2(pos), f->GetRect()))
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
    if (!Gameover)
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
}

void GameModel::ManipulateTime(TIME_ENUM t)
{
    //WE probably dont need any checks
    if (!Gameover)
    {
        speedOfTime = t;
    }
}

//Is called every gametick by Causality
//Handles: tax
//         [here be more thing]
void GameModel::Update()
{
    //Check if we game over
    if (satisfaction < -10)
    {
        Gameover = true;
    }
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
                tax += dynamic_cast<IndustrialZone*>(f)->GetWorkers() * stat._finState.GetIndustrialTaxRate();
                break;
            case SERVICEZONE:
                tax += dynamic_cast<ServiceZone*>(f)->GetWorkers() * stat._finState.GetServiceTaxRate();
                break;
            case RESIDENTALZONE:
                tax += dynamic_cast<ResidentalZone*>(f)->GetResidents() * stat._finState.GetResidentialTaxRate();
                break;
            default:
                //Unreachable
                break;
            }
        }
        stat._finState.total_founds -= tax;
    }

    //Calculate satisfaction
    int new_sat = 10; //starting satisfaction
    //Adók ha 0.5 alatt vannak + 1, amúgy -1
    if (stat._finState.GetIndustrialTaxRate() < 0.5) {new_sat += 1;} else {new_sat -= 1;}
    if (stat._finState.GetResidentialTaxRate() < 0.5) {new_sat += 1;} else {new_sat -= 1;}
    if (stat._finState.GetServiceTaxRate() < 0.5) {new_sat += 1;} else {new_sat -= 1;}

    //közel := x (mondjuk 3) távolságon belüli DFSs-ben mérve
    //Ha a lakóhelyhez van közel munkahely (industrial, service) +1, -1 residental zone mezönkéne * residents
    //Ha a lakóhelyhez nincs közel ipari épület (industrial) +1, -1 residental zone mezönkéne * residents
    //Van e a közelben rendőrség, +1, -1 residental zone mezönkéne * residents
    //TODO +Erdő.age * 0.1, mezönként
    int numOfIndustrial = 0, numOfService = 0;
    for (auto f : _fields)
    {
        switch (f->GetId())
        {
            case INDUSTRIALZONE:
                numOfIndustrial++;
                break;
            case SERVICEZONE:
                numOfService++;
                break;
            case RESIDENTALZONE:
                //közeli munkahely
                //közeli ipari épület
                //van e rendőrség
                //erdő
                break;
            default:
                //nothing
                //it lehetne csalni hogy nem nézünk távolságokat csak hogy hány erdő, rendérség van az alapján +
                break;
        }
    }

    //Csak negítív
    //Ha total_funds < 0, (total_funds / 1000), vagyis ha hitel van
    if (stat._finState.total_founds < 0)
    {
        new_sat += (stat._finState.total_founds / 1000); // jó a += mert az érték negatív
    }
    // (|servicezone| - |industrialzone| / X) * -1    //X = 2
    // Ha kiegyensúlyozatlan a szone, izone arány
    new_sat -= abs(numOfIndustrial - numOfService)/2;
    satisfaction = new_sat;
}