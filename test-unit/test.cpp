#include <catch2/catch_test_macros.hpp>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../src/UserAccount.cpp" // implimentation is in the .cpp not .h

TEST_CASE("INVALID USER ACCOUNT: BAD USERNAME - '.' at beginning") {
    std::string username = ".johndoe";
    std::string password = "password123456";
    std::string role = "employee";
    bool valid = isValid_User(username, password, role);
    REQUIRE(valid == false);
}

TEST_CASE("INVALID USER ACCOUNT: BAD USERNAME - '.' at end") {
    std::string username = "johndoe.";
    std::string password = "password123456";
    std::string role = "employee";
    REQUIRE(isValid_User(username, password, role) == false);
}

TEST_CASE("INVALID USER ACCOUNT: BAD USERNAME - no '.'") {
    std::string username = "johndoe";
    std::string password = "password123456";
    std::string role = "employee";
    REQUIRE(isValid_User(username, password, role) == false);
}

TEST_CASE("INVALID USER ACCOUNT: BAD PASSWORD - under 10 characters") {
    std::string username = "john.doe";
    std::string password = "password";
    std::string role = "employee";
    REQUIRE(isValid_User(username, password, role) == false);
}

TEST_CASE("INVALID USER ACCOUNT: BAD ROLE - not admin, manager, or employee") {
    std::string username = "john.doe";
    std::string password = "password";
    std::string role = "person";
    REQUIRE(isValid_User(username, password, role) == false);
}

TEST_CASE("VALID USER ACCOUNT 1") {
    std::string username = "john.doe";
    std::string password = "password123456";
    std::string role = "employee";
    REQUIRE(isValid_User(username, password, role) == true);
}

TEST_CASE("VALID USER ACCOUNT 2") {
    std::string username = "J.T";
    std::string password = "1234567890";
    std::string role = "manager";
    REQUIRE(isValid_User(username, password, role) == true);
}

TEST_CASE("VALID USER ACCOUNT 3") {
    std::string username = "user.name";
    std::string password = "is_this_a_pswrd?";
    std::string role = "admin";
    REQUIRE(isValid_User(username, password, role) == true);
}