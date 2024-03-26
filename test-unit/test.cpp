#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <math.h>
#define private public

TEST_CASE("1: Testing power of 1") {
    REQUIRE(1 == 1);
}