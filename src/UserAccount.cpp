#include "UserAccount.h"

bool isValid_User(string& u, string& p, string& l) {
    bool valid_username = false;
    bool valid_password = false;
    bool valid_level = false;
    unordered_set<string> lo_levels;
    lo_levels.insert("administrator");
    lo_levels.insert("manager");
    lo_levels.insert("employee");

    // Check if u is a valid username:
    size_t period_pos = u.find('.');
    if (period_pos != string::npos && period_pos != 0 && period_pos != u.length() - 1) {
        valid_username = true;
    }

    // check if p is a valid password (Parameters: must be at least 10 characters long)
    if (p.length() >= 10) {
        valid_password = true;
    }

    // check if l is in the list of levels assigned to employees
    if (lo_levels.find(l) != lo_levels.end()) {
        valid_level = true;
    }

    // final check
    if (valid_username && valid_password && valid_level) {
        return true;
    }
    else {
        if (!valid_username) {
            cout << "Invalid username" << endl;
        }
        if (!valid_password) {
            cout << "Invalid password" << endl;
        }
        if (!valid_level) {
            cout << "Invalid level title" << endl;
        }
        return false;
    }
}

UserAccount::UserAccount(string& u, string& p, string& l) : username(u), password(p), level(l) {
    cout << "User: " << username << " has been created." << endl;
}

