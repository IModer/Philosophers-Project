#ifndef MODEL_H_DEFINED
#define MODEL_H_DEFINED

#include <filesystem>
#include "../App/global.h"
#include "../Persistence/Persistence.h"
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

        int numOfSaves;
        const string savesPath = "./saves/";

        //Gameplay variables
        const int StartingCash = 10000;
        const int StartingTaxRate = 10;

        INT_TOUPLE _fields_dim = INT_TOUPLE{100,50};

        GameModel(Persistence* persistence) 
        {
            //Init _persistance ans _fields
            _persistence = persistence;
            _fields = list<Field*>();
            stat._finState = finantial_state();
            speedOfTime = NORMAL;
            
            //numOfSaves beállítása
            numOfSaves = 0;
            for (const auto & entry : filesystem::directory_iterator(savesPath))
            {
                if (entry.path().extension() == ".sf")
                {
                    numOfSaves++;
                }
            }

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
        
        FloatingWindow* GetFWindow() { return _fWindow; }
        void CloseFWindow() { delete _fWindow; _fWindow = nullptr; }
        void NewGame();
        void SaveGame();
        void LoadGame(int savenum);
        void Update();
        void ChechInfrastructure();
        bool Build(FIELD_TYPES field_t, INT_TOUPLE pos);
        bool Demolition(INT_TOUPLE p); 
        void CauseCatastrophe();
        void ManipulateTime(TIME_ENUM t);
        void SendFireDepartment(INT_TOUPLE p);
        void OnFieldClick(INT_TOUPLE p);

        bool checkCoordsInPlayField(INT_TOUPLE pos);
        void TickTock();

        //
        INT_TOUPLE GetBuildingSize(Field* f) {return BuildingSizes.at((FIELD_TYPES)(f->GetId()));}

        //Setters for Tax rates
        void SetResidentialTaxRate(int num) {stat._finState.SetResidentialTaxRate(num);}
        void SetIndustrialTaxRate(int num) {stat._finState.SetIndustrialTaxRate(num);}
        void SetServiceTaxRate(int num) {stat._finState.SetServiceTaxRate(num);}
        //Maybe also getter?

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
            for (auto  f : _fields)
            {
                total += GetBuildingMaintenanceCost(f);
            }
            return total;
        };

    private:
    FloatingWindow* _fWindow;

    void Causality();

};

#endif