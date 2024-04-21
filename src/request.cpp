#include <iostream>
#include <string>
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
    //username = user;
    //password = pass;
    //user_role = role;
    //assigned_projects = projects;

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
