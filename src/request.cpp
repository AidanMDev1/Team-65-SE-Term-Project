#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#define CURL_STATICLIB
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
        }
        curl_easy_cleanup(curl);
    }
    //parse through response_data to find user details and store into request class variables
    //since rn it returns smth like {["id":"someid", "username":"someusername", "password":"somepassword", etc.]}
    string delimiter = ",";
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

    res[0].erase(res[0].begin());
    res[res.size()-1].erase(res[res.size()-1].end()-1);
   
    std::vector<std::string> res2;
    std::string temp2;

    for (int i = 0; i<res.size(); i++){
        for(int j = 0; j<res[i].size(); j++){
            if(res[i].at(j) == ':'){
                string temp = res[i];
                temp2 = temp.substr(j + 1, res[i].length() - 1);
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

    size_t open_bracket = response_data.find("[");
    size_t close_bracket = response_data.find("]");
    string projectTemp = response_data.substr(open_bracket + 1, close_bracket - open_bracket-1);

    std::string token2;
    std::vector<std::string> projects;
    size_t start2 = 0;

   
    for (size_t found = projectTemp.find(delimiter); found != string::npos; found = projectTemp.find(delimiter, start2)) 
    {
        projects.emplace_back(projectTemp.begin() + start2, projectTemp.begin() + found);
        start2 = found + delimiter.size();
    }
    if (start2 != projectTemp.size()){
         projects.emplace_back(projectTemp.begin() + start2, projectTemp.end());
    }
    
    for(int i = 0; i<projects.size(); i++){
        size_t quotes = projects[i].find("\"");
        projects[i].erase(projects[i].begin() + quotes);

        size_t quotes2 = projects[i].find("\"");
        projects[i].erase(projects[i].begin() + quotes2);
    }
    
    username = res2[1]; 
    password = res2[2];
    user_role = res2[3];
    assigned_projects = projects;

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
            if (response_data == "null")
            {
                return false;
            }
        }
        curl_easy_cleanup(curl);
    }
    return true;
};

bool request::check_user(string user)
{
    string param = "api/check_user/" + user;
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
        }
        curl_easy_cleanup(curl);
    }
    return true;
}
bool request::check_user_project(string user, string project)
{
    string param = "api/check_user_project/" + user + "/" + project;
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
        }
        curl_easy_cleanup(curl);
    }
    return true;
};

bool request::assign_user(string user, string proj)
{
    string param = "api/assign_user/" + user + "/" + proj;
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
            if (response_data == "null")
            {
                return false;
            }
        }
        curl_easy_cleanup(curl);
    }
    return true;
};

bool request::send_notification(string user, string from, string notif)
{
    string param = "api/send_notification/" + user + "/" + from + "/" + notif;
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
            if (response_data == "null")
            {
                return false;
            }
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
            if (response_data == "null")
            {
                return false;
            }
        }
        curl_easy_cleanup(curl);
    }
    return true;
};

bool request::check_time(string user, string project)
{
    string param = "api/check_time/" + user + "/" + project;
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
        }
        curl_easy_cleanup(curl);
    }
    return true;
};

bool request::create_clockin(string user, string project)
{
    string param = "api/create_clockin/" + user + "/" + project;
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
        }
        curl_easy_cleanup(curl);
    }
    return true;
};

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
            if (response_data == "null")
            {
                return false;
            }
        }
        curl_easy_cleanup(curl);
    }
    return true;
};

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
            if (response_data == "null")
            {
                return false;
            }
        }
        curl_easy_cleanup(curl);
    }
    return true;
};

bool request::create_project(string project, string project_manager, string client)
{
    string param = "api/create_project/" + project + "/" + project_manager + "/" + client;
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
        }
        curl_easy_cleanup(curl);
    }
    return true;
};

bool request::check_project(string project)
{
    string param = "api/check_project/" + project;
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
        }
        curl_easy_cleanup(curl);
    }
    return true;
};

bool request::edit_project(string project, string project_manager, string client)
{
    string param = "api/edit_project/" + project + "/" + project_manager + "/" + client;
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
        }
        curl_easy_cleanup(curl);
    }
    return true;
};

bool request::get_manager_projects(string project_manager)
{
    string param = "api/manager_projects/" + project_manager;
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
        }
        curl_easy_cleanup(curl);
    }
    return true;
};

bool request::total_time_create(string username)
{
    string param = "api/total_time_create/" + username;
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
        }
        curl_easy_cleanup(curl);
    }
    return true;
};

bool request::total_time_update(string username, string time)
{
    string param = "api/total_time_update/" + username + "/" + time;
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
        }
        curl_easy_cleanup(curl);
    }
    return true;
};

bool request::get_total_time(string username)
{
    string param = "api/get_total_time/" + username;
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
        }
        curl_easy_cleanup(curl);
    }
    size_t timePos = response_data.find("\"time_worked\"");
    if (timePos != string::npos) {
        // Find the start and end of the value string for time_worked
        size_t timeStart = response_data.find_first_of(":", timePos);
        size_t timeEnd = response_data.find_first_of(",", timeStart + 1);
        time_worked = response_data.substr(timeStart + 2, timeEnd - timeStart - 3);

    }
    return true;
};

vector<string> request::get_project_members(string project)
{
    string param = "api/project_members/" + project;
    string req = url + param;
    string response_data;
    vector<string> usernames;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, req.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;

        } else {

            size_t pos = response_data.find("\"username\"");
            while (pos != string::npos) {
                size_t colonPos = response_data.find(":", pos);
                if (colonPos != string::npos) {
                    size_t quotePos = response_data.find("\"", colonPos + 1);
                    if (quotePos != string::npos) {
                        size_t nextQuotePos = response_data.find("\"", quotePos + 1);
                        string username = response_data.substr(quotePos + 1, nextQuotePos - quotePos - 1);
                        usernames.push_back(username);
                    }
                }
                pos = response_data.find("\"username\"", pos + 1);
            }
        }
        curl_easy_cleanup(curl);
    }
    return usernames;
};

vector<string> request::get_clockin(string user, string project)
{
    string param = "api/get_clockin/" + user + "/" + project;
    string req = url + param;
    string response_data;
    vector<string> clockin_times;
    vector<string> times;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, req.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;

        } else {

            size_t pos = response_data.find("\"clockin\"");
            if (pos != string::npos) {
                // Find the first occurrence of "[" after "clockin"
                size_t startBracketPos = response_data.find("[", pos);
                if (startBracketPos != string::npos) {
                    // Find the position of the closing "]"
                    size_t endBracketPos = response_data.find("]", startBracketPos);
                    if (endBracketPos != string::npos) {
                        // Extract the substring containing clockin times
                        string clockinSubstring = response_data.substr(startBracketPos + 1, endBracketPos - startBracketPos - 1);

                        // Use stringstream to tokenize the clockin times
                        stringstream ss(clockinSubstring);
                        string token;
                        while (getline(ss, token, ',')) {
                            // Remove leading and trailing whitespaces and store the entire token
                            size_t firstChar = token.find_first_not_of(" \t\"");
                            size_t lastChar = token.find_last_not_of(" \t\"");
                            if (firstChar != string::npos && lastChar != string::npos) {
                                times.push_back(token.substr(firstChar, lastChar - firstChar + 1));
                            }
                        }
                    }
                }
            }
            for(int i = 0; i < times.size();i+=2){
                clockin_times.push_back(times[i] + ", " + times[i+1]);
            };
        }
        curl_easy_cleanup(curl);
    }
    return clockin_times;
};
vector<string> request::get_clockout(string user, string project)
{
    string param = "api/get_clockout/" + user + "/" + project;
    string req = url + param;
    string response_data;
    vector<string> clockout_times;
    vector<string> times;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, req.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;

        } else {

            size_t pos = response_data.find("\"clockout\"");
            if (pos != string::npos) {
                size_t startBracketPos = response_data.find("[", pos);
                if (startBracketPos != string::npos) {
                    size_t endBracketPos = response_data.find("]", startBracketPos);
                    if (endBracketPos != string::npos) {
                        string clockoutSubstring = response_data.substr(startBracketPos + 1, endBracketPos - startBracketPos - 1);
                        stringstream ss(clockoutSubstring);
                        string token;
                        while (getline(ss, token, ',')) {
                            size_t firstChar = token.find_first_not_of(" \t\"");
                            size_t lastChar = token.find_last_not_of(" \t\"");
                            if (firstChar != string::npos && lastChar != string::npos) {
                                times.push_back(token.substr(firstChar, lastChar - firstChar + 1));
                            }
                        }
                    }
                }
            }
            for(int i = 0; i < times.size();i+=2){
                clockout_times.push_back(times[i] + ", " + times[i+1]);
            };
        }
        curl_easy_cleanup(curl);
    }
    return clockout_times;
}
vector<string> request::get_project_info(string project)
{
        string param = "api/get_project_info/" + project;
    string req = url + param;
    string response_data;
    vector<string> project_info;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, req.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;

        } else {

            size_t namePos = response_data.find("\"project_name\"");
            size_t managerPos = response_data.find("\"project_manager\"");
            size_t clientPos = response_data.find("\"client\"");

            if (namePos != string::npos && managerPos != string::npos && clientPos != string::npos) {
                // Find the start and end of the value string for project_name
                size_t nameStart = response_data.find_first_of(":", namePos);
                size_t nameEnd = response_data.find_first_of(",", nameStart + 1);
                project_info.push_back(response_data.substr(nameStart + 2, nameEnd - nameStart - 3));

                // Find the start and end of the value string for project_manager
                size_t managerStart = response_data.find_first_of(":", managerPos);
                size_t managerEnd = response_data.find_first_of(",", managerStart + 1);
                project_info.push_back(response_data.substr(managerStart + 2, managerEnd - managerStart - 3));

                // Find the start and end of the value string for client
                size_t clientStart = response_data.find_first_of(":", clientPos);
                size_t clientEnd = response_data.find_first_of(",", clientStart + 1);
                project_info.push_back(response_data.substr(clientStart + 2, clientEnd - clientStart - 3));
            }
        }
        curl_easy_cleanup(curl);
    }
    return project_info;
};

