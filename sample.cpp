#include <iostream>
#include <string>
#include <curl/curl.h>

// Callback function to write received data into a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT); // Initialize libcurl

    curl = curl_easy_init(); // Create a curl handle
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/posts/1"); // Set the URL
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // Set the callback function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer); // Pass the string buffer to the callback

        res = curl_easy_perform(curl); // Perform the request

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "API Response:\n" << readBuffer << std::endl;
        }

        curl_easy_cleanup(curl); // Clean up the curl handle
    }

    curl_global_cleanup(); // Clean up libcurl
    return 0;
}
