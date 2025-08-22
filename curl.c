#include <stdio.h>
#include <curl/curl.h> // Include libcurl header
#include <iostream.h>
// Callback function to write received data
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((char*)userp)[0] = '\0'; // Clear buffer (for simplicity, only storing first chunk)
    strncat((char*)userp, (char*)contents, size * nmemb);
    return size * nmemb;
}

int main(void) {
    CURL *curl;
    CURLcode res;
    char response_buffer[4096]; // Buffer to store the response

    curl_global_init(CURL_GLOBAL_DEFAULT); // Initialize libcurl global environment

    curl = curl_easy_init(); // Initialize a curl easy handle
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/posts/1"); // Set the URL
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback); // Set the callback function for writing data
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response_buffer); // Pass the buffer to the callback

        res = curl_easy_perform(curl); // Perform the request

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("Response: %s\n", response_buffer); // Print the received response
        }

        curl_easy_cleanup(curl); // Clean up the curl easy handle
    }
    curl_cleanup();
    curl_global_cleanup(); // Clean up libcurl global environment

    return 0;
}
