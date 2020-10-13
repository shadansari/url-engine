#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
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
            case 'h': usage(); break;
            case 'a': usage(); break;
            default: usage(); exit(EXIT_FAILURE);
        }
    }

    if (argc - optind != 2) {
        printf("Invalid number of arguments\n");
        usage();
        exit(EXIT_FAILURE);
    }

    conf = argv[optind];
    url = argv[optind+1];

    procConf(conf, &sets);

    if (!sets) {
        printf("No input pattern sets!\n");
        exit(EXIT_SUCCESS);
    }

    procUrl(url, sets);

    exit(EXIT_SUCCESS);
}
