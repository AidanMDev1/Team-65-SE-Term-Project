#pragma once
#include <iostream>
#include <string>
#include <curl/curl.h>
using namespace std;

class request{
private:
    CURL *curl;
    CURLcode res;
    string url = "http://localhost:6500/";

public:
    string get_allusers();
    bool login(string user, string pass);
    bool create_user(string user, string pass, string role, string project);
    bool delete_user(string user);
    bool send_notification(string user, string notif);
    bool check_notification(string user);
    bool delete_notification(string user, string notif);
};
