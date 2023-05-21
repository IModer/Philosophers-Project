//#define TEST //FOR CODING
#ifdef TEST

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
// Run unit tests

// Model

// Persistence

#include "../Persistence/Persistence.h"
#include "../Model/GameModel.h"
#include "../Model/RoadsAndElectricPoles.h"
#include "../Model/Forest.h"
#include "../Model/FireDepartment.h"
#include "../Model/PowerPlant.h"
#include "../Model/Stadion.h"
#include "../Model/ResidentalZone.h"
#include "../Model/ServiceZone.h"
#include "../Model/IndustrialZone.h"

TEST_CASE("1", "initialisation of objects")
{
    auto gameModel = new GameModel();
    CHECK(typeid(gameModel) == typeid(GameModel));
}

// TEST_CASE("1", "Sikeres beolvasás")
// {
//     auto p = new Persistence();

//     try
//     {
//         auto _fields = list<Field*>();
//         auto _fin_state = finantial_state{};
//         time_t time = 0;
//         auto stat = Stat(time, _fin_state);
//         p->readGameState("tests/persistence_readtest1.txt", _fields, stat);

//         auto _fin_state_currect = finantial_state{};
//         auto stat_currect = Stat(0, _fin_state_currect);
//         // auto _fields_correct = list<Field*>();
//         // _fields_correct.push_back(new RoadsAndElectricPoles(    ROADANDELECTRICPOLE,    INT_TOUPLE{1,0},    INT_TOUPLE{1,1},    0));
//         // _fields_correct.push_back(new Forest(                   FOREST,                 INT_TOUPLE{2,0},    INT_TOUPLE{1,1},    2));
//         // _fields_correct.push_back(new FireDepartment(           FIREDEPARTMENT,         INT_TOUPLE{3,0},    INT_TOUPLE{2,2},    12));
//         // _fields_correct.push_back(new PowerPlant(               POWERPLANT,             INT_TOUPLE{4,0},    INT_TOUPLE{1,1}));
//         // _fields_correct.push_back(new Stadion(                  STADIUM,                INT_TOUPLE{5,0},    INT_TOUPLE{1,1}));
//         // _fields_correct.push_back(new ServiceZone(              SERVICEZONE,            INT_TOUPLE{6,0},    INT_TOUPLE{1,1},    1));
//         // _fields_correct.push_back(new IndustrialZone(           INDUSTRIALZONE,         INT_TOUPLE{7,0},    INT_TOUPLE{1,1},    1));
//         // _fields_correct.push_back(new ResidentalZone(           RESIDENTALZONE,         INT_TOUPLE{8,0},    INT_TOUPLE{1,1},    1));
//         //CHECK _fields
//         auto fc_front = _fields.begin();

//         //RoadsAndElectricPoles
//         std::advance(fc_front, 0);
//         CHECK((*fc_front)->toString() == "1 1 0 1 1 0" );

//         //Forest
//         std::advance(fc_front, 1);
//         CHECK((*fc_front)->toString() == "3 2 0 1 1 0 1 0 1 0 11 2" );

//         //FireDepartment
//         std::advance(fc_front, 1);
//         CHECK((*fc_front)->toString() == "4 3 0 2 2 1 0 1 0 1 12" );

//         //PowerPlant
//         std::advance(fc_front, 1);
//         CHECK((*fc_front)->toString() == "5 4 0 1 1 0 1 0 1 13 1" );

//         //Stadion
//         std::advance(fc_front, 1);
//         CHECK((*fc_front)->toString() == "6 5 0 1 1 1 1 1 1 14" );

//         //ServiceZone
//         std::advance(fc_front, 1);
//         CHECK((*fc_front)->toString() == "7 6 0 1 1 0 0 0 0 15 1 1" );

//         //IndustrialZone
//         std::advance(fc_front, 1);
//         CHECK((*fc_front)->toString() == "8 7 0 1 1 0 0 0 0 16 1 1" );

//         //ResidentalZone
//         std::advance(fc_front, 1);
//         CHECK((*fc_front)->toString() == "9 8 0 1 1 0 0 0 0 0 0 17 1" );

//         CHECK(stat_currect._finState.GetIndustrialTaxRate() == stat._finState.GetIndustrialTaxRate());
//         CHECK(stat_currect._finState.GetResidentialTaxRate() == stat._finState.GetResidentialTaxRate());
//         CHECK(stat_currect._finState.GetServiceTaxRate() == stat._finState.GetServiceTaxRate());
//         //CHECK(stat_currect._finState.get == stat._fin_state.total_founds);
//     }
//     catch(IOException& e)
//     {
//         std::cerr << e.what() << '\n';
//     }
// }

// TEST_CASE("2", "Sikertelen beolvasás")
// {
//     auto p = new Persistence();
//     auto _fields = list<Field*>();
//     auto _fin_state = finantial_state{};
//     time_t time = 0;
//     auto stat = Stat(time, _fin_state);
//     CHECK_THROWS(p->readGameState("NO_SUCH.FILE", _fields, stat));

// }

#endif // TEST