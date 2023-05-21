//#define TEST

#ifdef TEST

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Model/GameModel.h" 


TEST_CASE("GameModel Tests", "[GameModel]") {
    Persistence persistence;  // Create a mock Persistence object for testing
    GameModel gameModel(&persistence);  // Create an instance of GameModel

    SECTION("Initial Game Model State") {
        // Verify the initial state of GameModel
        REQUIRE(gameModel._fields.empty());
        REQUIRE(gameModel.speedOfTime == NORMAL);
        REQUIRE(gameModel.Gameover == false);
        REQUIRE(gameModel.satisfaction == gameModel.StartingSatisfaction);
        // Add more assertions for other members as needed
    }

    SECTION("Building Functions") {
        // Test the Build function
        SECTION("Build Residential Field") {
            INT_TOUPLE temp = {0,0};
            std::vector<INT_TOUPLE>* t_vec;
            t_vec->push_back(temp);
            bool result = gameModel.Build(RESIDENTIALZONE, t_vec);
            REQUIRE(result == true);
            // Add additional assertions to verify the state after building a residential field
        }

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

    // Add more test sections to cover other functionality of GameModel
}

#endif