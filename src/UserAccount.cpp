#include "UserAccount.h"

/* this is for user account creation (once in main)
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
   } */

bool isValid_User(std::string& u, std::string& p, std::string& r) {
    bool valid_username = false;
    bool valid_password = false;
    bool valid_role = false;
    std::unordered_set<std::string> lo_roles;
    lo_roles.insert("admin");
    lo_roles.insert("manager");
    lo_roles.insert("employee");

    // Check if u is a valid username:
    size_t period_pos = u.find('.');
    if (period_pos != std::string::npos && period_pos != 0 && period_pos != u.length() - 1) {
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
    return false;
}

UserAccount::UserAccount(std::string& u, std::string& p, std::string& r) : username(u), password(p), role(r) {
    std::cout << "User: " << username << " has been created." << std::endl;
}