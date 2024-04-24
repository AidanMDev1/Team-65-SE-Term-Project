#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
using namespace std;

class request{
private:
    CURL *curl;
    CURLcode res;
    string url = "http://localhost:6500/";

public:
    string username;
    string password;
    string user_role;
    vector<string> assigned_projects;
    string time_worked;

    string get_allusers();
    bool login(string user, string pass);
    bool create_user(string user, string pass, string role, string project);
    bool check_user(string user);
    bool check_user_project(string user, string project);
    bool assign_user(string user, string proj);
    bool delete_user(string user);
    bool send_notification(string user, string from, string notif);
    bool check_notification(string user);
    bool delete_notification(string user, string notif);
    bool check_time(string user, string project);
    bool create_clockin(string user, string project);
    bool clockin(string user, string project);
    bool clockout(string user, string project);
    bool create_project(string project, string project_manager, string client);
    bool check_project(string project);
    bool edit_project(string project, string project_manager, string client);
    bool get_manager_projects(string project_manager);
    bool total_time_create(string username);
    bool total_time_update(string username, string time);
    bool get_total_time(string username);

    vector<string> get_project_members(string project);
    vector<string> get_clockin(string user, string project);
    vector<string> get_clockout(string user, string project);
    vector<string> get_project_info(string project);

};
