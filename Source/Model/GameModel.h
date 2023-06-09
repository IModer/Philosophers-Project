#ifndef MODEL_H_DEFINED
#define MODEL_H_DEFINED

#include <filesystem>
#include "../App/global.h"
#include "../Persistence/Persistence.h"
#include "FireDepartment.h"
#include "FloatingWindow.h"
#include "enum/time_enum.h"
#include "IndustrialZone.h"
#include "ServiceZone.h"

using namespace std;

class GameModel
{
    public:
        Persistence* _persistence;
        list<Field*> _fields;
        //finantial_state _fin_state;
        Stat stat;

        TIME_ENUM speedOfTime;

        bool Gameover;


        int numOfSaves;
        const string savesPath = "./saves/";

        //Gameplay variables
        const int StartingCash = 1000000;  //loan of a small million dollar
        const double StartingTaxRate = 0.3;
        const int StartingSatisfaction = 100;
        const int MinSatisfaction = 0;

        int satisfaction = StartingSatisfaction;
        //TODO modifiers for easier balancing, like from satisfaction calculation

        INT_TOUPLE StartingRoadCoords = INT_TOUPLE{0,-1300};

        INT_TOUPLE _fields_dim = INT_TOUPLE{100,50};

        INT_TOUPLE _fields_corner_topleft = INT_TOUPLE{-2500 ,-1250};
        INT_TOUPLE _fields_corner_rightbottom = INT_TOUPLE{ 2450 , 1200};

        GameModel(Persistence* persistence) 
        {
            //Init _persistance and _fields
            _persistence = persistence;
            _fields = list<Field*>();
            stat._finState = finantial_state();
            speedOfTime = NORMAL;
            Gameover = false;
            
            //numOfSaves beállítása
            getNumOfSaves();

            //Init FloatingWindow
            _fWindow = nullptr;
        };

        void OpenFWindow(Field* f) 
        {
            if(_fWindow != nullptr)
            {
                delete _fWindow;
            } 
            _fWindow = new FloatingWindow(f); 
        };

        int getNumOfSaves() {
            numOfSaves = 0;
            for (const auto & entry : filesystem::directory_iterator(savesPath))
            {
                if (entry.path().extension() == ".sf")
                {
                    numOfSaves++;
                }
            }
            return numOfSaves;
        }

        bool SaveFileExsists(int n) {
            filesystem::path f{ savesPath + "savefile" + STR(n) + ".sf" };
            return  filesystem::exists(f);
        }
        
        FloatingWindow* GetFWindow() { return _fWindow; }
        void CloseFWindow() { delete _fWindow; _fWindow = nullptr; }
        void NewGame();
        void SaveGame(int savenum=1);
        void LoadGame(int savenum);
        //Ö checkeli hogy gameover van-e 
        void Update();
            void HandleProfit();
        void CheckInfrastructure();
            void CheckHasSpecialFieldNearby();

        //Ezek csak akkor mennek ha nem gameover
        bool Build(FIELD_TYPES field_t, vector<INT_TOUPLE>* poses);
        bool Demolition(Vector2 p); 
        void CauseCatastrophe();
        void ManipulateTime(TIME_ENUM t);
        void SendFireDepartment(INT_TOUPLE p);
        void TickTock();
        
        void OnFieldClick(INT_TOUPLE p);

        bool checkCoordsNotInPlayField(INT_TOUPLE pos);

        INT_TOUPLE GetBuildingSize(Field* f) {return BuildingSizes.at((FIELD_TYPES)(f->GetId()));}

        //fancy getter for date
        string GetCurrentDate()
        {
            //60 ticktock egy nap
            int days = (stat._time / 60) % 30;
            int months = ((stat._time / 60) / 30) % 12; 
            int years = ((stat._time / 60) / 30) / 12;
            return STR(1990 + years) + ". " + STR(1 + months) + ". " +  STR(1 + days);
        };

        //Setters for Tax rates
        void SetResidentialTaxRate(float num) {stat._finState.SetResidentialTaxRate(num);}
        void SetIndustrialTaxRate(float num) {stat._finState.SetIndustrialTaxRate(num);}
        void SetServiceTaxRate(float num) {stat._finState.SetServiceTaxRate(num);}

        float GetResidentialTaxRate() { return stat._finState.GetResidentialTaxRate(); }
        float GetIndustrialTaxRate() { return stat._finState.GetIndustrialTaxRate(); }
        float GetServiceTaxRate() { return stat._finState.GetServiceTaxRate(); }

        //A kiadási oldalhoz
        int GetBuildingCost(Field* f) {return BuildCosts.at((FIELD_TYPES)(f->GetId()));}
        int GetBuildingMaintenanceCost(Field* f) {return BuildingMaintenanceCost.at((FIELD_TYPES)(f->GetId()));}

        //Költségvetéses oldalhoz

        int GetTotalIncame() 
        {
            int total = 0;
            for (auto  f : _fields)
            {
                switch (f->GetId())
                {
                case INDUSTRIALZONE:
                    total += (dynamic_cast<IndustrialZone*>(f))->GetProfit();
                    break;
                case SERVICEZONE:
                    total += dynamic_cast<ServiceZone*>(f)->GetProfit();
                    break;
                default:
                    // Nothing
                    break;
                }
            }
            return total;
        };
        int GetTotalSpending()
        {
            int total = 0;
            for (auto f : _fields)
            {
                total += GetBuildingMaintenanceCost(f);
            }
            return total;
        };

    FireDepartment* GetClosestFireDepartment(Field* field) {
        FireDepartment* fd = nullptr;
        for (Field* f : _fields) {
            if (f->GetId() == FIREDEPARTMENT) {
                FireDepartment* tmp = (FireDepartment*)f;
                if (tmp->InRange(field)) {
                    if (tmp->getACount() == 0) return tmp;
                    if (fd == nullptr || fd->getACount() > tmp->getACount()) fd = tmp;
                }
            }
        }
        return fd;
    };
    
    private:
    FloatingWindow* _fWindow;

    void Causality();

};

#endif