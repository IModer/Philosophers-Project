#ifdef TEST

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Model/GameModel.h" 

TEST_CASE("GameModel", "[Constructor]") {
    Persistence persistence; // Create a Persistence object
    GameModel gameModel(&persistence); // Create a GameModel object using the Persistence object

    // Verify initial values
    REQUIRE(gameModel._persistence == &persistence);
    REQUIRE(gameModel._fields.empty());
    REQUIRE(gameModel.speedOfTime == NORMAL);
    REQUIRE(gameModel.Gameover == false);
    REQUIRE(gameModel.satisfaction == gameModel.StartingSatisfaction);
    // Add more assertions for other members if needed
}

#endif