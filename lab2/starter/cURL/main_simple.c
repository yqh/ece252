/*
 * Copyright(c) 2018-2019 Yiqing Huang, <yqhuang@uwaterloo.ca>.
 *
 * This software may be freely redistributed under the terms of the X11 License.
 */

/**
 * @file main_simple.c
 * @brief Using cURL to get request a URL and output the response
 *        from the server to standard output
 * SYNOPSIS
 *      <command> [URL]
 * NOTES: -DDEBUG_1 will show more debugging messages to stderr
 */ 
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

#define IMG_URL "http://ece252-1.uwaterloo.ca:2520/image?img=1"
#define DUM_URL "https://example.com/"

int main( int argc, char** argv ) 
{
    CURL *curl_handle;
    CURLcode res;
    char url[256];

    if (argc == 1) {
        strcpy(url, IMG_URL); 
    } else {
        strcpy(url, argv[1]);
    }
#ifdef DEBUG_1
    fprintf(stderr, "%s: URL is %s\n", argv[0], url);
#endif /* DEBUG_1 */
    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl_handle = curl_easy_init();
    if(curl_handle) {
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        res = curl_easy_perform(curl_handle);

        if( res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl_handle);
    }

    curl_global_cleanup();
    return 0;
}
