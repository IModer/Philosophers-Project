#ifdef TEST

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Model/GameModel.h"  // Include the header file of the class you want to test

// Write your unit tests using the Catch2 macros
TEST_CASE("GameModel Tests", "[GameModel]") {
    // Write your test cases
    SECTION("Test 1") {
        // Test code
        REQUIRE(1 + 1 == 2);
    }

    SECTION("Test 2") {
        // Test code
        REQUIRE(2 * 2 == 4);
    }

    // Add more test cases as needed
}

#endif