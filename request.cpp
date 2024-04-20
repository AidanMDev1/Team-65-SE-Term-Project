#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#define CURL_STATICLIB
#include "curl/curl.h"
#include "request.h"

using namespace std;
size_t write_callback(void *ptr, size_t size, size_t nmemb, string *data) 
{
    size_t total_size = size * nmemb;
    data->append((char*)ptr, total_size);
    return total_size;
};

string request::get_allusers()
{
    string param = "api/allusers";
    string req = url + param;
    string response_data;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, req.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        } else {
            cout << "Response: " << response_data << endl;
        }

        curl_easy_cleanup(curl);
    }
    return response_data;
};

bool request::login(string user, string pass)
{
    string param = "api/login/" + user + "/" + pass;
    string req = url + param;
    string response_data;
    vector<string> user_info;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, req.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            return false;
        } else {
            cout << "Response: " << response_data << endl;
        }

        curl_easy_cleanup(curl);
    }
    
    //parse through response_data to find user details and store into request class variables
    //since rn it returns smth like {["id":"someid", "username":"someusername", "password":"somepassword", etc.]}

    string delimiter = ", ";
    size_t pos_start = 0, pos_end, delim_length = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = response_data.find(delimiter, pos_start)) != std::string::npos) {
        token = response_data.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_length;
        res.push_back (token);
    }

    res.push_back (response_data.substr (pos_start));

    res[0] = res[0].substr(2, res[0].length());

    std::vector<std::string> res2;
    std::string temp2;
    std::cout << res[0] << std::endl;
     username = user;

    for (int i = 0; i<res.size(); i++){
         std::cout << res[i] << std::endl;
        for(int j = 0; j<res[i].size(); j++){ //"id":"name"
            if(res[i].at(j) == ':'){ //:"name"
                
                string temp = res[i]; // "id":"name"
                temp2 = temp.substr(j + 2, res[i].length() - 1); //name
                res2.push_back(temp2);
            }
        }
    }

    username = res2[1]; //
    password = res2[2];
    user_role = res2[3];
    assigned_projects = res[4]; //the assigned_projects parsing part might not work 

    //username = user
    //passward=pass;
    //user_role=role;
    //assigned_projects=projects;
    return true;
};

bool request::create_user(string user, string pass, string role, string project)
{
    string param = "api/create_user/" + user + "/" + pass + "/" + role + "/" + project;
    string req = url + param;
    string response_data;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, req.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            return false;
        } else {
            cout << "Response: " << response_data << endl;
        }

        curl_easy_cleanup(curl);
    }
    return true;
};

bool request::delete_user(string user)
{
    string param = "api/delete_user/" + user;
    string req = url + param;
    string response_data;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, req.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            return false;
        } else {
            cout << "Response: " << response_data << endl;
        }

        curl_easy_cleanup(curl);
    }
    return true;
};

bool request::send_notification(string user, string notif)
{
    string param = "api/send_notification/" + user + "/" + notif;
    string req = url + param;
    string response_data;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, req.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            return false;
        } else {
            cout << "Response: " << response_data << endl;
        }

        curl_easy_cleanup(curl);
    }
    return true;
};

bool request::check_notification(string user)
{
    string param = "api/notifications/" + user;
    string req = url + param;
    string response_data;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, req.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            return false;
        } else {
            cout << "Response: " << response_data << endl;
        }

        curl_easy_cleanup(curl);
    }
    return true;
};

bool request::delete_notification(string user, string notif)
{
    string param = "api/delete_notification/" + user + "/" + notif;
    string req = url + param;
    string response_data;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, req.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            return false;
        } else {
            cout << "Response: " << response_data << endl;
        }

        curl_easy_cleanup(curl);
    }
    return true;
};

