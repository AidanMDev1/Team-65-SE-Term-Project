#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include "request.h"

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
            if (response_data == "null")
            {
                return false;
            }
            cout << "Response: " << response_data << endl;
        }

        curl_easy_cleanup(curl);
    }
    //parse through response_data to find user details and store into request class variables
    //since rn it returns smth like {["id":"someid", "username":"someusername", "password":"somepassword", etc.]}
    string delimiter = ",";
    size_t pos_start = 0, pos_end, delim_length = delimiter.length();
    std::string token;
    std::vector<std::string> res;
    size_t start = 0;

    for (size_t found = response_data.find(delimiter); found != string::npos; found = response_data.find(delimiter, start))
    {
        res.emplace_back(response_data.begin() + start, response_data.begin() + found);
        start = found + delimiter.size();
    }
    if (start != response_data.size()){
         res.emplace_back(response_data.begin() + start, response_data.end());
    }

    res[0].erase(res[0].begin()); //erase first bracket
    res[res.size()-1].erase(res[res.size()-1].end()-1); //erase last bracket
   
    std::vector<std::string> res2;
    std::string temp2;

    for (int i = 0; i<res.size(); i++){
        for(int j = 0; j<res[i].size(); j++){ //"id":"name"
            if(res[i].at(j) == ':'){ //:"name"
                string temp = res[i]; // "id":"name"
                temp2 = temp.substr(j + 1, res[i].length() - 1); //name
                res2.push_back(temp2);
            }
        }
    }

    for(int i = 0; i<res2.size()-1; i++){
        size_t quotes = res2[i].find("\"");
        res2[i].erase(res2[i].begin() + quotes);

        size_t quotes2 = res2[i].find("\"");
        res2[i].erase(res2[i].begin() + quotes2);
    }

    username = res2[1]; 
    password = res2[2];
    user_role = res2[3];
    assigned_projects.push_back(res2[4]); //assigned as [projectName], if error check this first
    // std::cout << res2.size() << std::endl;
    // std::cout << username << std::endl;
    // std::cout << password << std::endl;
    // std::cout << user_role << std::endl;
    // for (int i = 0; i < assigned_projects.size(); i++){
    //     std::cout << assigned_projects[i] << std::endl;
    // }
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
}
bool request::clockin(string user, string project)
{
    string param = "api/clockin/" + user + "/" + project;
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
}
bool request::clockout(string user, string project)
{
    string param = "api/clockout/" + user + "/" + project;
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
