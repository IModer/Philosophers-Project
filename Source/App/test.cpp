//#define TEST
#ifdef TEST

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Model/GameModel.h"  // Include the header file of the class you want to test
#include "global.h"

// Write your unit tests using the Catch2 macros
TEST_CASE("GameModel Tests", "[GameModel]") {
    Persistence persistence;  // Create a mock Persistence object for testing
    GameModel gameModel(&persistence);  // Create an instance of GameModel

    SECTION("Initial Game Model State") {
        // Verify the initial state of GameModel
        //gameModel.NewGame();
        REQUIRE(gameModel._fields.empty());
        REQUIRE(gameModel.speedOfTime == NORMAL);
        REQUIRE(gameModel.Gameover == false);
        REQUIRE(gameModel.satisfaction == gameModel.StartingSatisfaction);
        // Add more assertions for other members as needed
    }

    /*SECTION("Build Residential Field") {
        INT_TOUPLE temp = {0,0};
        std::vector<INT_TOUPLE>* t_vec;
        t_vec->push_back(temp);
        bool result = gameModel.Build(RESIDENTALZONE, t_vec);
        REQUIRE(result == true);
        // Add additional assertions to verify the state after building a residential field
    }*/

    SECTION("Build Industrial Field") {
        INT_TOUPLE temp = {0,0};
        std::vector<INT_TOUPLE>* t_vec;
        t_vec->push_back(temp);
        bool result = gameModel.Build(INDUSTRIALZONE, t_vec);
        REQUIRE(result == false);
        // Add additional assertions to verify the state after building an industrial field
    }

    // Add more test cases for other building functions

}

TEST_CASE("Persistance good", "[Persistance 1]")
{
    auto p = new Persistence();
    auto _fields = list<Field*>();
    auto _fin_state = finantial_state{};
    time_t time = 0;
    auto stat = Stat(time, _fin_state);
    
    SECTION("Write test")
    {
        CHECK_NOTHROW(p->writeGameState("tests/persistance_writetest1.txt", _fields, stat));
    }

    SECTION("Read test")
    {
        p->readGameState("tests/persistance_readtest1.txt", _fields, stat);
        //Stat check
        CHECK(stat._time == 1);
        CHECK(stat._finState.total_founds == 2);
        CHECK(stat._finState.loan == 3);
        CHECK(stat._finState.GetResidentialTaxRate() == 4);
        CHECK(stat._finState.GetIndustrialTaxRate() == 5);
        CHECK(stat._finState.GetServiceTaxRate() == 6);

        CHECK(_fields.size() == 9);

        for (auto g : _fields)
        {
            CHECK(g->GetId() == FOREST); 
        }
        
    }
}

TEST_CASE("Persistance bad", "[Persistance 2]")
{
    auto p = new Persistence();
    auto _fields = list<Field*>();
    auto _fin_state = finantial_state{};
    time_t time = 0;
    auto stat = Stat(time, _fin_state);

    SECTION("Bad reading"){
        CHECK_THROWS(p->readGameState("NO_SUCH.FILE", _fields, stat));
    }

    SECTION("Bad writing")
    {
        CHECK_THROWS(p->writeGameState("NO_SUCH.FILE", _fields, stat));
    }
}


#endif
