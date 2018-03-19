#define CURL_STATICLIB
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  while (1) {
    size_t message_size = 0;
    for (int i = 0; i < 4; i++) {
      message_size = message_size | (getchar() << i*8);
    }

    char *message = malloc(message_size + 1);
    for (int i = 0; i < message_size; i++) {
      message[i] = getchar();
    }

    message[message_size] = '\0';

    // POST to web server
    CURL *ch = curl_easy_init();
    
    // Build headers
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    
    curl_easy_setopt(ch, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(ch, CURLOPT_URL, "http://localhost:7171");
    curl_easy_setopt(ch, CURLOPT_POSTFIELDS, message);

    // Make request
    curl_easy_perform(ch);

    // Cleanup
    curl_easy_cleanup(ch);
    curl_slist_free_all(headers);
    free(message);
  }
}
