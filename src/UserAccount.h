#pragma once
using namespace std;
#include <string>
#include <iostream>
#include <unordered_set>

bool isValid_User(string& u, string& p, string& l);

class UserAccount {
private:
    string username;
    string password;
    string level;
public:
    UserAccount(string& u, string& p, string& l);

};