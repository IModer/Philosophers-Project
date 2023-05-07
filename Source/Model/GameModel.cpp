#include "GameModel.h"
#include "IndustrialZone.h"
#include "ServiceZone.h"
#include "ResidentalZone.h"
#include "Zone.h"
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <set>
//#include <raylib.h>

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
    CheckInfrastructure();
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
    //ChechInfrastructure();
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

        CheckInfrastructure();  //Update the infrastructure
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
                CheckInfrastructure();
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
    //Maybe only check every 60 calls, roughly every second
    if (stat._time % 60 == 0)
        Update();       //Check if we need to do thing 

    //printf("%s\n", GetCurrentDate().c_str());
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
//Handles:  tax
//          satisfaction
//          residents and workers
void GameModel::Update()
{
    ////Check if we game over
    if (satisfaction < -10)
    {
        Gameover = true;
    }
    
    ////Tax
    //We tax every month
    if ((stat._time / 60) % 30 == 0)
    {
        //Go through every field, tax according to the num of residents/workers
        auto tax = 0;
        for (auto f : _fields)
        {
            switch ((FIELD_TYPES)f->GetId())
            {
            case INDUSTRIALZONE:
                tax += dynamic_cast<IndustrialZone*>(f)->GetWorkers() * stat._finState.GetIndustrialTaxRate() / 12;
                break;
            case SERVICEZONE:
                tax += dynamic_cast<ServiceZone*>(f)->GetWorkers() * stat._finState.GetServiceTaxRate() / 12;
                break;
            case RESIDENTALZONE:
                tax += dynamic_cast<ResidentalZone*>(f)->GetResidents() * stat._finState.GetResidentialTaxRate() / 12;
                break;
            default:
                //Unreachable
                break;
            }
        }
        stat._finState.total_founds -= tax;
    }

    ////Calculate satisfaction
    // ez lehetne csak naponta

    int new_sat = 10; //starting satisfaction
    //Adók ha 0.5 alatt vannak + 1, amúgy -1
    //TODO súlyozni kell total_residents el
    if (stat._finState.GetIndustrialTaxRate() < 0.5) {new_sat += 1;} else {new_sat -= 1;}
    if (stat._finState.GetResidentialTaxRate() < 0.5) {new_sat += 1;} else {new_sat -= 1;}
    if (stat._finState.GetServiceTaxRate() < 0.5) {new_sat += 1;} else {new_sat -= 1;}

    //közel := x (mondjuk 3) távolságon belüli DFSs-ben mérve
    //Ha a lakóhelyhez van közel munkahely (industrial, service) +1, -1 residental zone mezönkéne * residents
    //Ha a lakóhelyhez nincs közel ipari épület (industrial) +1, -1 residental zone mezönkéne * residents
    //Van e a közelben rendőrség, +1, -1 residental zone mezönkéne * residents
    //TODO + Erdő.age * 0.1, mezönként
    int numOfIndustrial = 0;
    int numOfService = 0;
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
                //TODO_DFS
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
    //TODO súlyozni kell total_residents el
    if (stat._finState.total_founds < 0)
    {
        new_sat += (stat._finState.total_founds / 1000); // jó a += mert az érték negatív
    }
    // (|servicezone| - |industrialzone| / X) * -1    //X = 2
    // Ha kiegyensúlyozatlan a s-zone, i-zone arány
    //TODO súlyozni kell total_residents el
    new_sat -= abs(numOfIndustrial - numOfService)/2;
    satisfaction = new_sat;

    ////New people coming to the city

    //Megnézzük mennyi hely van
    int freeSpace = 0;
    auto freeSpaceFields = list<ResidentalZone*>();
    for (auto f : _fields)
    {
        //Residental zone és be van kötve az utakhoz
        if (f->GetId() == RESIDENTALZONE && dynamic_cast<GameField*>(f)->GetIsConnectedToRoad()) 
        {
            auto cf = dynamic_cast<ResidentalZone*>(f);
            freeSpace += cf->GetMaxresidents() - cf->GetResidents();
            freeSpaceFields.push_back(cf);
        }
    }
    
    //Ha van hely
    if (freeSpace > 0)
    {
        srand(time(NULL));
        //Valamennyi valószinűséggel jön valaki minden házba
        for (auto f : freeSpaceFields)
        {
            int chanceOfMovingIn = 50;
            //TODO_DFS if (VAN KÖZELBE FA) {chanceOfMovingIn += 10}
            //TODO_DFS van e közelben szabad munkahely, nincs közelben ipari hely
            chanceOfMovingIn += satisfaction*2;
            if ((rand() % 100) >= chanceOfMovingIn) //50% valószinűség az alap
            {
                f->MoveResidentsIn(1);
            }
        }
    }

    ////Munkába menetel
    //hetente
    if ((stat._time / 60) % 7 == 0)
    {
        //Minden emberhez próbálunk munkát osztani hetente aki nem tud munkába menni elköltözik
        int totalResidents;

        for (auto f : _fields)
        {
            if (f->GetId() == RESIDENTALZONE && dynamic_cast<GameField*>(f)->GetIsConnectedToRoad()) 
            {
                auto cf = dynamic_cast<ResidentalZone*>(f);
                totalResidents += cf->GetResidents();
            }
        }

        int foundWorkplace = 0;
        int leftToPutToWork = totalResidents;
        //lenullázni minden industrial/service mező worker-jét
        for (auto f : _fields)
        {
            if (f->GetId() == INDUSTRIALZONE || f->GetId() == SERVICEZONE)
            {
                if (f->GetId() == INDUSTRIALZONE)
                {
                    auto cf = dynamic_cast<IndustrialZone*>(f);
                    cf->SetWorker(0);

                } else if (f->GetId() == SERVICEZONE)
                {
                    auto cf = dynamic_cast<ServiceZone*>(f);
                    cf->SetWorker(0);
                }
            }
        }
        //Megnézzük van e munkahely ahova tudna menni
        for (auto f : _fields)
        {
            //residental vagy service és be van kötve 
            if (leftToPutToWork > 0 && (f->GetId() == INDUSTRIALZONE || f->GetId() == SERVICEZONE) && dynamic_cast<GameField*>(f)->GetIsConnectedToRoad()) 
            {
                int space = 0;
                if (f->GetId() == INDUSTRIALZONE)
                {
                    auto cf = dynamic_cast<IndustrialZone*>(f);
                    space = min(leftToPutToWork, cf->GetMaxWorkers() - cf->GetWorkers());
                    if (space > 0)
                    {
                        //Annyit beosztunk amennyit lehet
                        cf->SetWorker(space);
                        leftToPutToWork -= space;
                    }

                } else if (f->GetId() == SERVICEZONE)
                {
                    auto cf = dynamic_cast<ServiceZone*>(f);
                    space = min(leftToPutToWork, cf->GetMaxWorkers() - cf->GetWorkers());
                    if (space > 0)
                    {
                        //Annyit beosztunk amennyit lehet
                        cf->SetWorker(space);
                        leftToPutToWork -= space;
                    }
                }
            }
        }

        //Those who didnt find any workplace leave the city :(
        int haveToMoveOut = leftToPutToWork;
        for (auto f : _fields)
        {
            if (haveToMoveOut > 0 && f->GetId() == RESIDENTALZONE && dynamic_cast<GameField*>(f)->GetIsConnectedToRoad())
            {
                auto cf = dynamic_cast<ResidentalZone*>(f);
                int res = min(haveToMoveOut,cf->GetResidents());
                if (res > 0)
                {
                    cf->MoveResidentsOut(res);
                    haveToMoveOut -= res;
                }
            }
        }
    }
}

//Kéne asszem:
//Megnészi van e egy X hosszú körben van e erdő (végtelen norma)
//CheckIsForrestInRange(GameField* f)

//Megnézi hogy van t tipusú mezű az f r sugarú környezetében
//CheckIsFIELD_TYPEInRange(GameField* f, FIELD_TYPE t, int r)

//

void GameModel::CheckInfrastructure() 
{
    ////Utak megnézése
    
    //Először mindenkit false ra rakunk
    for (auto f : _fields)
    {
        auto cf = dynamic_cast<GameField*>(f);
        cf->SetIsConnectedToRoad(false);
    }
    
    //Kiindulunk a kezdő ütból ami pályán kívül van
    auto queue = std::queue<INT_TOUPLE>();
    auto visited = std::set<INT_TOUPLE>();
    queue.push(StartingRoadCoords);
    while (!queue.empty())
    {
        auto v = queue.front(); queue.pop();
        if (visited.count(v) == 0)
        {
            //Visit
            visited.insert(v);
            //v minden út szomszédják berakjuk a queue-ba
            //Ha a szomszéd nem út akkor beálltjuk hogy isConnectedToRoads
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (checkCoordsInPlayField(INT_TOUPLE{v.x+i, v.y+j}))
                    {
                        //itt lehetne az egyszer kifejtett mártix szerint menni csak akkor elötte ki kell fejteni a mátrixba a _fields-t
                        for (auto f : _fields)
                        {
                            if (f->GetX() == v.x+i && f->GetY() == v.y+j)
                            {
                                //Itt amúgy csak a road lenne jó, de electric pole még nincs úgy se 
                                if (f->GetId() == ROADANDELECTRICPOLE)
                                {
                                    //Ha út akkor megyünk a mentén
                                    queue.push(INT_TOUPLE{f->GetX(), f->GetY()});
                                } else if (f->GetId() != GAMEFIELD && f->GetId() != FOREST) {
                                    auto cf = dynamic_cast<GameField*>(f);
                                    cf->SetIsConnectedToRoad(true);
                                }
                            }
                        }
                        
                    }
                }   
            }

        }
    }
};