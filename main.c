#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "common.h"

struct set_rec* sets = NULL;

void usage() {
    printf("usage: url-engine <algorithm(posix|self)> configuration.xml urls.txt\n");
}

int main(int argc, char *argv[]) {
    int opt;
    const char* conf;
    const char* url;

    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch (opt) {
            case 'h': usage(); exit(EXIT_SUCCESS);
            default: usage(); exit(EXIT_FAILURE);
        }
    }

    if (argc - optind == 3) {
        if (!strcmp(argv[optind], "self")) {
            printf("The \"self\" matching algorithm is not supported\n");
            exit(EXIT_FAILURE);
        } else if (!strcmp(argv[optind], "posix")) {
            // posix regexp matching is supported
        } else {
            usage(); exit(EXIT_FAILURE);
        }
        conf = argv[optind+1];
        url = argv[optind+2];
    } else if (argc - optind == 2) {
        conf = argv[optind];
        url = argv[optind+1];
    } else {
        printf("Invalid number of arguments\n");
        usage();
        exit(EXIT_FAILURE);
    }

    procConf(conf, &sets);

    if (!sets) {
        printf("No input pattern sets!\n");
        exit(EXIT_SUCCESS);
    }

    procUrl(url, sets);

    exit(EXIT_SUCCESS);
}
