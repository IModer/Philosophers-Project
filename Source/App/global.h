#ifndef _GLOBAL_
#define _GLOBAL_

#include "raylib.h"
#include <map>

#include <string>
//this might be bad
#include <sstream>
#include <vector>
#include <istream>
#include <stdexcept>
#include <iostream>

#ifdef debug
#include <iostream>
#endif

#if __linux__
#include <bits/types/time_t.h>

#elif _WIN32 | _WIN64
#include <time.h>

#endif

#define STR(x) std::to_string(x)
#define V2_TO_IT(v) INT_TOUPLE{static_cast<int>(v.x), static_cast<int>(v.y)}
#define IT_TO_V2(it) Vector2{static_cast<float>(it.x), static_cast<float>(it.y)}

typedef struct INT_TOUPLE { 
    int x, y;
    std::string toString() {
        return STR(x) + " " + STR(y);
    }
} INT_TOUPLE;

//Ids for Field types

typedef enum {
    ROADANDELECTRICPOLE = 1,
    GAMEFIELD = 2,
    FOREST = 3,
    FIREDEPARTMENT = 4,
    POWERPLANT = 5,
    STADIUM = 6,
    SERVICEZONE = 7,
    INDUSTRIALZONE = 8,
    RESIDENTALZONE = 9,
    POLICESTATION = 10
} FIELD_TYPES;

typedef enum {
    BT_DEMOLISH = -1,
    BT_NULL = 0,
    BT_ROADANDELECTRICPOLE = 1,
    BT_GAMEFIELD = 2,
    BT_FOREST = 3,
    BT_FIREDEPARTMENT = 4,
    BT_POWERPLANT = 5,
    BT_STADIUM = 6,
    BT_SERVICEZONE = 7,
    BT_INDUSTRIALZONE = 8,
    BT_RESIDENTALZONE = 9,
    BT_POLICESTATION = 10
} BUILD_TYPES;

const int FPS = 60;
const int M_UNIT = 50;

const std::map<FIELD_TYPES, Rectangle> SourceRects = {
    {ROADANDELECTRICPOLE, {0, 0, 0, 0}},
    {FOREST, {50, 120, 50, 60}},
    {FIREDEPARTMENT, {100, 60, 50, 60}},
    {POWERPLANT, {150, 60, 50, 60}},
    {STADIUM, {50, 60, 50, 60}},
    {SERVICEZONE, {0, 120, 50, 60}},
    {INDUSTRIALZONE, {200, 60, 50, 60}},
    {RESIDENTALZONE, {0, 0, 50, 60}},
    {POLICESTATION, {0, 60, 50, 60}}
};

const Rectangle fireSourceRect[2] = {{100, 120, 50, 60}, {150, 120, 50, 60}};

//This can be tweaked any time to balace the game, maybe it can even scale with time or money spent, ect...
//Scaleing wouldnt be that hard, int scale = x; 50*scale, 100*scale ...
const std::map<FIELD_TYPES, int> BuildCosts = {
    {ROADANDELECTRICPOLE,    50},
    {FOREST,                100},
    {FIREDEPARTMENT,       1000},
    {POWERPLANT,           2000},
    {STADIUM,              4000},
    {SERVICEZONE,          2000},
    {INDUSTRIALZONE,       3000},
    {RESIDENTALZONE,       1000},
    {POLICESTATION,        1000}
};

const std::map<FIELD_TYPES, std::string> BuildingNames = {
    {ROADANDELECTRICPOLE,  "Road"},
    {FOREST,               "Forest"},
    {FIREDEPARTMENT,       "Fire department"},
    {POWERPLANT,           "Powerplant"},
    {STADIUM,              "Stadium"},
    {SERVICEZONE,          "Service zone"},
    {INDUSTRIALZONE,       "Industrial zone"},
    {RESIDENTALZONE,       "Residental zone"},
    {POLICESTATION,        "Police station"}
};

// I think we should use this, but this needs refactoring
const std::map<FIELD_TYPES, INT_TOUPLE> BuildingSizes = {
    {ROADANDELECTRICPOLE,  INT_TOUPLE{1,1}},
    {FOREST,               INT_TOUPLE{1,1}},
    {GAMEFIELD,            INT_TOUPLE{0,0}},
    {FIREDEPARTMENT,       INT_TOUPLE{2,2}},  //could be 1x1
    {POWERPLANT,           INT_TOUPLE{2,2}},
    {STADIUM,              INT_TOUPLE{2,2}},  //Could be 3x3
    {SERVICEZONE,          INT_TOUPLE{1,1}},
    {INDUSTRIALZONE,       INT_TOUPLE{1,1}},
    {RESIDENTALZONE,       INT_TOUPLE{1,1}},
    {POLICESTATION,        INT_TOUPLE{1,1}}
};

// I think we should also use this, but this also needs refactoring
const std::map<FIELD_TYPES, int> BuildingMaintenanceCost= {
    {ROADANDELECTRICPOLE,  100},
    {FOREST,               100},
    {FIREDEPARTMENT,       0},
    {POWERPLANT,           0},
    {STADIUM,              100},  
    {SERVICEZONE,          0},
    {INDUSTRIALZONE,       0},
    {RESIDENTALZONE,       0},
    {POLICESTATION,        100}
};



typedef enum { MENU = 0, LOAD, GAME } GAME_STATE;

struct finantial_state
{
private:
    //float 0-1 között
    float residential_tax_rate;
    float industrial_tax_rate;
    float service_tax_rate;

public:
    int total_founds;
    int loan;

    float GetResidentialTaxRate() {return residential_tax_rate;}
    float GetIndustrialTaxRate() {return industrial_tax_rate;}
    float GetServiceTaxRate() {return service_tax_rate;}

    void SetResidentialTaxRate(float num)
    {
        if (num > 1 || num < 0)
            num = 0;
            // throw std::invalid_argument("Invalid argument passed to SetResidentialTaxRate. num should be in range [0,1]");
        residential_tax_rate = num;
    }

    void SetIndustrialTaxRate(float num)
    {
        if (num > 1 || num < 0)
            num = 0;
            // throw std::invalid_argument("Invalid argument passed to SetIndustrialTaxRate. num should be in range [0,1]");
        
        industrial_tax_rate = num;
    }

    void SetServiceTaxRate(float num)
    {
        if (num > 1 || num < 0)
            num = 0;
            // throw std::invalid_argument("Invalid argument passed to SetServiceTaxRate. num should be in range [0,1]");
        
        service_tax_rate = num;
    }

    std::string toString() {
        return STR(total_founds) + " " + STR(loan) + " " + STR(residential_tax_rate) + " " + STR(industrial_tax_rate) + " " + STR(service_tax_rate);
    }
    
    friend std::ostream & operator<<(std::ostream& is, finantial_state& f)
    {
        is  <<  f.total_founds            << " " <<
                f.loan                    << " " << 
                f.residential_tax_rate    << " " <<
                f.industrial_tax_rate     << " " <<
                f.service_tax_rate  << " " << std::endl;
        return is;
    }

    friend std::ostream & operator>>(std::stringstream& is, finantial_state& f)
    {
        //TODO Handle error, also maybe we could use the setter
        std::string s_total_founds; std::string s_loan; std::string s_residential_tax_rate;
        std::string s_industrial_tax_rate; std::string s_entertainment_tax_rate;
        is >> s_total_founds >> s_loan >> s_residential_tax_rate >> s_industrial_tax_rate >> s_entertainment_tax_rate;

        f.total_founds = std::stoi(s_total_founds);
        f.loan = std::stoi(s_loan);
        f.residential_tax_rate = std::stoi(s_residential_tax_rate);
        f.industrial_tax_rate = std::stoi(s_industrial_tax_rate);
        f.service_tax_rate = std::stoi(s_entertainment_tax_rate);
        
        return is;
    }
};

#endif