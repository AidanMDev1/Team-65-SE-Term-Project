#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include "request.h"
using namespace std;

int main(){
    request req;
    bool test = false;

    //uncoment the functionality you want to test

    //string response = req.get_allusers();

    // test = req.login("Brian", "pass4");
    // if (test)
    // {
    //     cout << req.username << endl;
    //     cout << req.password << endl;
    //     cout << req.user_role << endl;
    //     for (int i = 0; i < req.assigned_projects.size(); i++)
    //     {
    //         cout << req.assigned_projects[i] << endl;
    //     }
    // };

    // test = req.get_total_time("Brian");
    // if (test){
    //     cout << req.time_worked << endl;
    //     cout << req.total_clockin << endl;

    vector<string> senders = req.get_sender("Brian");
    cout << senders.size() << endl;
    for (int i = 0; i < senders.size(); i++)
    {
        cout << "this is sender " << i << ": " << senders[i] << endl;
    }

    vector<string> notifs = req.get_notifications("Brian");
    cout << notifs.size() << endl;
    for (int i = 0; i < notifs.size(); i++)
    {
        cout << "this is notif " << i << ": " << notifs[i] << endl;
    }




    // vector<string> users = req.get_project_members("pacman");
    // cout << users.size() << endl;
    // for (int i = 0; i < users.size(); i++)
    // {
    //     cout << "this is user " << i << ": " << users[i] << endl;
    // }


    // vector<string> clockin_times = req.get_clockin("Brian", "questclock");
    // for (int i = 0; i < clockin_times.size(); i++)
    // {
    //     cout << "clockin #" << i << ": " << clockin_times[i] << endl;
    // }

    // vector<string> clockout_times = req.get_clockout("Brian", "questclock");
    // for (int i = 0; i < clockout_times.size(); i++)
    // {
    //     cout << "clockout #" << i << ": " << clockout_times[i] << endl;
    // }

    // vector<string> project_info = req.get_project_info("pacman");
    // cout << project_info.size() << endl;
    // cout << "project title: " << project_info[0] << endl;
    // cout << "project manager: " << project_info[1] << endl;
    // cout << "project client: " << project_info[2] << endl; 


    return 0;
}