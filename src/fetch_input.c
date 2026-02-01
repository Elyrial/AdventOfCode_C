#include "fetch_input.h"
#include "common.h"

#include <curl/curl.h>
#include <stdio.h>
#include <string.h>

static size_t
write_cb(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    Buffer *b = userdata;
    return buffer_append(b, ptr, size * nmemb) == 0
        ? size * nmemb
        : 0;
}

int
fetch_and_save_input(int year, int day, const char *session)
{
    CURL *curl;
    Buffer body;
    char url[256];
    char cookie[1024];
    char dir[128];
    char path[256];

    if (session == NULL || session[0] == '\0') {
        fprintf(stderr, "AOC_SESSION not set\n");
        return 1;
    }

    snprintf(url, sizeof(url),
             "https://adventofcode.com/%d/day/%d/input",
             year, day);

    snprintf(cookie, sizeof(cookie),
             "Cookie: session=%s", session);

    buffer_init(&body);

    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER,
                     curl_slist_append(NULL, cookie));

    if (curl_easy_perform(curl) != CURLE_OK) {
        fprintf(stderr, "curl failed\n");
        return 1;
    }

    str_rtrim_inplace(body.data);

    snprintf(dir, sizeof(dir), "inputs/year%d", year);
    ensure_dir_recursive(dir);

    snprintf(path, sizeof(path), "%s/day%02d.txt", dir, day);
    file_write_all(path, body.data, body.len);

    printf("Saved %s\n", path);

    buffer_free(&body);
    curl_easy_cleanup(curl);
    return 0;
}

