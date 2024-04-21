#pragma once
#include <string>
#include <iostream>
#include <unordered_set>

bool isValid_User(std::string& u, std::string& p, std::string& r);

class UserAccount {
private:
    std::string username;
    std::string password;
    std::string role;
public:
    UserAccount(std::string& u, std::string& p, std::string& r);
    ~UserAccount() { }

};