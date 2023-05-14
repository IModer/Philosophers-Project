#include "GameModel.h"
#include "GameField.h"
#include "IndustrialZone.h"
#include "ServiceZone.h"
#include "ResidentalZone.h"
#include "PowerPlant.h"
#include "Zone.h"
#include <raylib.h>
#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <unordered_set>
#include <algorithm>
//#include <raylib.h>

//#include "../View/View.h" // búúúúú
bool operator<(const INT_TOUPLE& it1, const INT_TOUPLE& it2) {
    return it1.x < it2.x && it1.y < it2.y; //! nemtom mi kéne
}

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
    satisfaction = StartingSatisfaction; //idk
    Gameover = false;
    CheckInfrastructure();
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
bool GameModel::Build(FIELD_TYPES field_t, vector<INT_TOUPLE>* poses) {
    if (!Gameover)
    {
        for (INT_TOUPLE pos : *poses) {
            //Building type alapján példányosítjuk
            auto f = Field::Factory(field_t, pos);
            if (f == nullptr)
            {
                continue; //Failed 
            }

            //Check if pos is a valid position in _fields
            if (checkCoordsNotInPlayField(pos)) {
                delete f;
                continue; //Failed
            }

            // Check all other buildings
            bool l = true;
            for(Field* i : _fields) {
                if (CheckCollisionRecs(f->GetRect(), i->GetRect())) {
                    if (i->GetId() == RESIDENTALZONE && f->GetId() == RESIDENTALZONE) {
                        ((ResidentalZone*)i)->Upgrade();
                        stat._finState.total_founds -= BuildCosts.at(field_t);
                    }
                    delete f;
                    l = false;
                    break;
                }
            }
            if (l) {
                _fields.push_back(f); //Build the field
                stat._finState.total_founds -= BuildCosts.at(field_t); //This might not be the best way to do it, we should check if we go into debt
            }
        }

        _fields.sort([](Field* f1, Field* f2){
            return f1->GetY() < f2->GetY();
        });
        CheckInfrastructure();  //Update the infrastructure
    }
    // does not recognise it. Does not work
    // else
    // {
    //     int button = MessageBox("This is a warning message!","Warning");
    // }
    return false;
} 

bool GameModel::Demolition(Vector2 pos) 
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
            if (CheckCollisionPointRec(pos, f->GetRect()))
            {
                //Check for conflicting demolish

                //Is it a road 
                    //Will it disconnect from the main road?
                        //If yes then resident should switch workplaces or leave the city

                //Is it a Residental Zone
                    //If yes then we
                _fields.remove(f);
                delete f;
                //TODO we can give back some small money like:
                //_fin_state.total_founds -= 0.2 * BuildCosts.at(f->GetId());
                CheckInfrastructure();
                return true;  //Demolished successfully
            }
        }
        return false; //Indicate that we didnt demolish 
    }
    return false;
}

void GameModel::CauseCatastrophe() {
    printf("oi\n");
    for (auto i : _fields) {
        if (i->GetId() != ROADANDELECTRICPOLE && rand()%100 < 50) ((GameField*)i)->SetOnFire();
    }
}

//Check if a pos is in the playing fields or not
bool GameModel::checkCoordsNotInPlayField(INT_TOUPLE pos)
{
    return pos.x > _fields_corner_rightbottom.x || pos.x < _fields_corner_topleft.x || pos.y < _fields_corner_topleft.y || pos.y > _fields_corner_rightbottom.y ;
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
//          profit
//          satisfaction
//          residents and workers
void GameModel::Update()
{
    ////Check if we game over
    if (satisfaction < MinSatisfaction)
    {
        Gameover = true;
    }

    // Building updates
    list<Field*>::iterator i = _fields.begin();
    while (i != _fields.end()) {
        if ((*i)->Update()) {
            _fields.erase(i++);
        } else i++;
    }


    //Profit
    int total_residents = 0;
    for (auto f : _fields)
    {
        if (f->GetId() == SERVICEZONE)
        {
            auto cf = dynamic_cast<ServiceZone*>(f);
            stat._finState.total_founds += cf->GetWorkers() * 50;
        }
        else if (f->GetId() == INDUSTRIALZONE)
        {
            auto cf = dynamic_cast<IndustrialZone*>(f);
            stat._finState.total_founds += cf->GetWorkers() * 100;
        }
        else if (f->GetId() == RESIDENTALZONE)
        {
            auto cf = dynamic_cast<ResidentalZone*>(f);
            total_residents += cf->GetResidents();
        }
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
        //Get money from tax
        stat._finState.total_founds += tax;
    }

    ////Calculate satisfaction
    // ez lehetne csak naponta

    int new_sat = StartingSatisfaction; //starting satisfaction
    //Adók ha 0.5 alatt vannak + 1, amúgy -1
    //súlyozni kell total_residents el
    if (stat._finState.GetIndustrialTaxRate()   < 0.5) {new_sat += 1 * (total_residents/2);}
                                                  else {new_sat -= 1 * total_residents;}
    if (stat._finState.GetResidentialTaxRate()  < 0.5) {new_sat += 1 * (total_residents/2);} 
                                                  else {new_sat -= 1 * total_residents;}
    if (stat._finState.GetServiceTaxRate()      < 0.5) {new_sat += 1 * (total_residents/2);}
                                                  else {new_sat -= 1 * total_residents;}

    //közel := x (mondjuk 3) távolságon belüli végtelen normában-ben mérve
    //Ha a lakóhelyhez van közel munkahely (industrial, service) +1, -1 residental zone mezönkéne * residents
    //Ha a lakóhelyhez nincs közel ipari épület (industrial) +1, -1 residental zone mezönkéne * residents
    //Van e a közelben rendőrség, +1, -1 residental zone mezönkéne * residents
    //TODO + Erdő.age * 0.1, mezönként
    int numOfIndustrial = 0;
    int numOfService = 0;
    int numOfResWithForrest = 0;
    int numOfResWithStadion = 0;
    int numOfResWithPolice = 0;
    for (auto f : _fields)
    {
        //TODO this can be an if/elseif
        switch (f->GetId())
        {
            case INDUSTRIALZONE:
                numOfIndustrial++;
                break;
            case SERVICEZONE:
                numOfService++;
                break;
            case RESIDENTALZONE:
                //TODO itt az erdő nem a kora szerint hat :(
                if (dynamic_cast<ResidentalZone*>(f)->GetHasForest()) {numOfResWithForrest++;}
                if (dynamic_cast<ResidentalZone*>(f)->GetHasPolice()) {numOfResWithPolice++;}
                if (dynamic_cast<ResidentalZone*>(f)->GetHasStadion()) {numOfResWithStadion++;}
                break;
            default:
                //nothing
                break;
        }
    }

    //TODO balance
    new_sat += total_residents*numOfResWithForrest/10;
    new_sat += total_residents*numOfResWithPolice/10;
    new_sat += total_residents*numOfResWithStadion/10;

    //Csak negítív
    //Ha total_funds < 0, (total_funds / 1000), vagyis ha hitel van
    if (stat._finState.total_founds < 0)
    {
        new_sat += (stat._finState.total_founds / 5000); // jó a += mert az érték negatív
    }
    // (|servicezone| - |industrialzone| / X) * -1    //X = 2
    // Ha kiegyensúlyozatlan a s-zone, i-zone arány
    //súlyozni kell total_residents el
    new_sat -= total_residents*abs(numOfIndustrial - numOfService)/10;
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
            if (cf->GetMaxresidents() - cf->GetResidents() > 0)
            {
                freeSpace += cf->GetMaxresidents() - cf->GetResidents();
                freeSpaceFields.push_back(cf);
            }
        }
    }
    
    //Ha van hely
    if (freeSpace > 0)
    {
        srand(time(NULL));
        //Valamennyi valószinűséggel jön valaki minden házba
        //van-e a közelben fa?
        for (auto f : freeSpaceFields)
        {
            int chanceOfMovingIn = 50;
            
            for(int i = f->GetPos().x - 150; i< f->GetPos().x + 150; i+=50)
            {
                for (int j = f->GetPos().y - 150; j< f->GetPos().y + 150; j+=50)
                {
                    for(auto g: _fields)
                    {
                        if (g->GetX() == i && g->GetY() == j)
                        {
                            if (g->GetId() == FOREST)
                            {
                                chanceOfMovingIn -= 10;
                            }
                            else if (g->GetId() == INDUSTRIALZONE)
                            {
                                chanceOfMovingIn += 1; //arbitrary, have no reason behind it whatsoever
                                if (dynamic_cast<IndustrialZone*>(g)->GetWorkers() < dynamic_cast<IndustrialZone*>(g)->GetMaxWorkers())
                                {
                                    chanceOfMovingIn -= 5;
                                }
                            }
                            else if (g->GetId() == SERVICEZONE)
                            {
                                chanceOfMovingIn += 1; //arbitrary, have no reason behind it whatsoever
                                if (dynamic_cast<ServiceZone*>(g)->GetWorkers() < dynamic_cast<ServiceZone*>(g)->GetMaxWorkers())
                                {
                                    chanceOfMovingIn -= 5;
                                }
                            }      
                        }    
                    }    
                }    
            }
            chanceOfMovingIn -= satisfaction*2;
            if ((rand() % 100) >= chanceOfMovingIn) //50% valószinűség az alap
            {
                f->MoveResidentsIn(1);
            }
        }
    }

    ////Munkába menetel
    //6 hónaponta
    if (((stat._time / 60) % (7*2)) == 0)
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
    auto queue = std::queue<Field*>();
    auto visited = std::unordered_set<Field*>();
    queue.push(new Field(FOREST, StartingRoadCoords));
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
                    if (!checkCoordsNotInPlayField(INT_TOUPLE{v->GetX()+(i * M_UNIT), v->GetY()+(j * M_UNIT)}))
                    {
                        //itt lehetne az egyszer kifejtett mártix szerint menni csak akkor elötte ki kell fejteni a mátrixba a _fields-t
                        //printf("BFS: %i %i\n", v.x+(i*M_UNIT), v.y+(j*M_UNIT));
                        for (auto f : _fields)
                        {
                            /*printf("BFS: check %i %i == %i %i != %i %i && %i \n", 
                            v->GetX()+(i*M_UNIT), v->GetY()+(j*M_UNIT), 
                            f->GetX(), f->GetY(), 
                            v->GetX(), v->GetY(), 
                            visited.count(f));
                            */
                            //Ha f ben megtaláltuk aki kell és az i! = j != 0 != i és még nem látogattuk meg ezt a pontot
                            if (f->GetX() == v->GetX()+(i*M_UNIT) &&
                                f->GetY() == v->GetY()+(j*M_UNIT) &&
                                !(v->GetX()+(i*M_UNIT) == v->GetX() && v->GetY()+(j*M_UNIT) == v->GetY()) &&
                                (visited.count(f) == 0))
                            {
                                //Itt amúgy csak a road lenne jó, de electric pole még nincs úgy se 
                                //printf("Yeppe\n");
                                if (f->GetId() == ROADANDELECTRICPOLE)
                                {
                                    //Ha út akkor megyünk a mentén
                                    queue.push(f);
                                    auto cf = dynamic_cast<GameField*>(f);
                                    cf->SetIsConnectedToRoad(true);
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

    //Elektromosság
    for (auto g : _fields)
    {
        if (g->GetId() == POWERPLANT)
        {
            printf("Here be dragons\n");
            auto cg = dynamic_cast<PowerPlant*>(g);
            //BFS over roads késöbb electric-pole on
            //miden ami nem ep (most még road) az costol valamennyi fuelt
            auto queue = std::queue<Field*>();
            auto visited = std::unordered_set<Field*>();
            //Mivel POWERPLANT 2x2 es, ez a legnagyonn heck amit valaha nyomtam
            auto cg1 = new PowerPlant(POWERPLANT,INT_TOUPLE{cg->GetX()+1*M_UNIT, cg->GetY()+1*M_UNIT});
            auto cg2 = new PowerPlant(POWERPLANT,INT_TOUPLE{cg->GetX()+1*M_UNIT, cg->GetY()+0});
            auto cg3 = new PowerPlant(POWERPLANT,INT_TOUPLE{cg->GetX()+0, cg->GetY()+1*M_UNIT});
            queue.push(cg); 
            queue.push(cg1); queue.push(cg2); queue.push(cg3);
            while (!queue.empty() && cg->GetCapacity() > 0)
            {
                auto v = queue.front(); queue.pop();
                if (visited.count(v) == 0)
                {
                    //printf("visit node: %s\n", v->toString().c_str());
                    visited.insert(v);
                    for (int i = -1; i <= 1; i++)
                    {
                        for (int j = -1; j <= 1; j++)
                        {
                            if (!checkCoordsNotInPlayField(INT_TOUPLE{v->GetX()+(i * M_UNIT), v->GetY()+(j * M_UNIT)}))
                            {
                                for (auto f : _fields)
                                {
                                    //printf("checking: %s\n", f->toString().c_str());
                                    if (f->GetX() == v->GetX()+(i*M_UNIT) &&
                                        f->GetY() == v->GetY()+(j*M_UNIT) &&
                                        !(v->GetX()+(i*M_UNIT) == v->GetX() && v->GetY()+(j*M_UNIT) == v->GetY()) &&
                                        (visited.count(f) == 0) &&
                                        (cg->GetCapacity() > 0))
                                    {
                                        //printf("passed: %s\n", f->toString().c_str());
                                        if (f->GetId() == ROADANDELECTRICPOLE)
                                        {
                                            //Ha út akkor csak megyünk a mentén
                                            queue.push(f);
                                            //TODO sok mindennek adhatnánk áramot, de most még csak SeriveZone/IndustrialZone-nak 
                                        } else if (f->GetId() == SERVICEZONE || f->GetId() == INDUSTRIALZONE) {
                                            queue.push(f);
                                            auto cf = dynamic_cast<GameField*>(f);
                                            if (!cf->GetHasElectricity())
                                            {
                                                cf->SetHasElectricity(true); cg->SetCapacity(cg->GetCapacity()-1);
                                            }
                                        }
                                    }
                                }    
                            }
                        }   
                    }

                }
            }
        }
    }
    

    //Erdők, stadion, rendőrség
    bool check_forest = false;
    bool check_stadion = false;
    bool check_police = false;
    for (auto f : _fields)
    {
        if (f->GetId() == RESIDENTALZONE)
        {
            for (int i = f->GetPos().x - 150; i <= f->GetPos().x + 150; i += 50)
            {
                for (int j = f->GetPos().y - 150; j <= f->GetPos().y + 150; j += 50)
                {
                    for (auto g : _fields)
                    {
                        if (g->GetX() == i && g->GetY() == j)
                        {
                            if (g->GetId() == FOREST)
                            {
                                check_forest = true;
                                //dynamic_cast<ResidentalZone *>(f)->SetHasForest(true);
                            }
                            else if (g->GetId() == STADIUM)
                            {
                                check_stadion = true;
                            }
                            else if (g->GetId() == POLICESTATION)
                            {
                                check_police = true;
                            }
                            
                        }
                    }
                }
            }
            dynamic_cast<ResidentalZone *>(f)->SetHasForest(check_forest);
            dynamic_cast<ResidentalZone *>(f)->SetHasStadion(check_stadion);
            dynamic_cast<ResidentalZone *>(f)->SetHasPolice(check_police);
        }
    }
};