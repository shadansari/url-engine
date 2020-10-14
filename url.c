#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include "common.h"

int procUrl(const char *filename, struct set_rec* sets) {
    const unsigned char *data;
    char buf[256];
    const unsigned char **p;

	if (NULL == (data = loadfile(filename))) {
        fprintf(stderr, "Error: Unable to load %s\n", filename);
		return 1;
	}

	p = &data;

    while (NULL != sgets(buf, sizeof(buf), p)) {
		// Remove pesky trailing newline
		char *newline = strchr(buf, '\n');
		if (newline)
			*newline = 0;
        char *host = strtok(buf, "/");
        char* path = strtok(NULL, "\0");
		match(host, path, sets);
	}

	return 0;
}
