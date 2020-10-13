#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include "common.h"

struct set_rec* sets = NULL;

void usage() {
    printf("usage: url-engine <algorithm(posix|self)> configuration.xml urls.txt\n");
}

int main(int argc, char *argv[]) {
    int opt;
    const char* xml_path;
    //const char* urls_path;

    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch (opt) {
            case 'h': usage(); break;
            case 'a': usage(); break;
            default: usage(); return EXIT_FAILURE;
        }
    }

    if (argc - optind != 2) {
        printf("Invalid number of arguments\n");
        usage();
        return EXIT_FAILURE;
    }

    xml_path = argv[optind];
    //urls_path = argv[optind+1];

    streamFile(xml_path, &sets);

    printf("sets found:\n");
    for (struct set_rec* s = sets; s != NULL; s = s->next) {
        printf("%s: ", s->val);
        for (struct pat_rec* p = s->pat; p != NULL; p = p->next) {
            printf("%s ", p->val);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}
