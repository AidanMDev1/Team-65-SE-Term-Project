#include "UserAccount.h"

bool isValid_User(string& u, string& p, string& r) {
    bool valid_username = false;
    bool valid_password = false;
    bool valid_role = false;
    unordered_set<string> lo_roles;
    lo_roles.insert("admin");
    lo_roles.insert("manager");
    lo_roles.insert("employee");

    // Check if u is a valid username:
    size_t period_pos = u.find('.');
    if (period_pos != string::npos && period_pos != 0 && period_pos != u.length() - 1) {
        valid_username = true;
    }

    // check if p is a valid password (Parameters: must be at least 10 characters long)
    if (p.length() >= 10) {
        valid_password = true;
    }

    // check if l is in the list of roles assigned to employees
    if (lo_roles.find(r) != lo_roles.end()) {
        valid_role = true;
    }

    // final check
    if (valid_username && valid_password && valid_role) {
        return true;
    }
    else {
        if (!valid_username) {
            cout << "Invalid username" << endl;
        }
        if (!valid_password) {
            cout << "Invalid password" << endl;
        }
        if (!valid_role) {
            cout << "Invalid role title" << endl;
        }
        return false;
    }
}

UserAccount::UserAccount(string& u, string& p, string& r) : username(u), password(p), role(r) {
    cout << "User: " << username << " has been created." << endl;
}

