#include <stdlib.h>

#include <curl/curl.h>

#include "log.h"

int main(int argc, char *argv[])
{
    INFOF("a");
    curl_global_init(CURL_GLOBAL_ALL);

    return EXIT_SUCCESS;
}