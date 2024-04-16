#include <iostream>
#include <string>
#include <./curl/curl.h>

// Callback function to write the response data to a buffer
size_t write_callback(void *ptr, size_t size, size_t nmemb, std::string *data) {
    size_t total_size = size * nmemb;
    data->append((char*)ptr, total_size);
    return total_size;
}

int main() {
    CURL *curl;
    CURLcode res;
    std::string url = "http://localhost:6500/api/createuser/Joe/4321/manager/project"; // Change this URL to the one you want to request

    // Initialize curl
    curl = curl_easy_init();
    if(curl) {
        // Set the URL to request
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the callback function to handle the response data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        // Allocate memory to store the response data
        std::string response_data;

        // Set the buffer to store the response data
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Print the response data
            std::cout << "Response: " << response_data << std::endl;
        }

        // Clean up
        curl_easy_cleanup(curl);
    }

    return 0;
}