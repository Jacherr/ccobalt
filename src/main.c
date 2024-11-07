#include <curl/curl.h>

int main(int argc, char *argv[])
{
    curl_global_init(CURL_GLOBAL_ALL);

    return 0;
}