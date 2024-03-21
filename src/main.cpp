#include <iostream>
#include "UserAccount.h"


int main() {
    string input_username;
    string input_password;
    string input_level;
    cout << "Username:";
    cin >> input_username;
    cout << "Password:";
    cin >> input_password;
    cout << "Role:";
    cin >> input_level;
    if (isValid_User(input_username, input_password, input_level)) {
        UserAccount user(input_username, input_password, input_level);
    }

    return 0;
}