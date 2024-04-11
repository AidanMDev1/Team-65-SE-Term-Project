#include <iostream>;
//#include <curl/curl.h>;
//#include <json/json.h>;


// Json::Value getData() {
//    CURL *curl;
//    CURLcode res;
//    Json::Value jsonData;

//    curl = curl_easy_init();
//    if (curl) {
//       curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:4000/");
//       curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &parseJson);
//       curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonData);
//       res = curl_easy_perform(curl);
//       curl_easy_cleanup(curl);
//    }
//    return jsonData;
// }
