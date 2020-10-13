#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

void procUrl(const char *filename, struct set_rec* sets) {
    FILE *fp;
	char *url = NULL;
	size_t len = 0;

    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Unable to open file %s", filename);
        exit(EXIT_FAILURE);
    }

    printf("sets:\n");
    for (struct set_rec* s = sets; s != NULL; s = s->next) {
        printf("%s: ", s->val);
        for (struct pat_rec* p = s->pat; p != NULL; p = p->next) {
            printf("%s:%s ", p->hostname, p->pathname);
        }
        printf("\n");
    }

    printf("urls:\n");
	while(getline(&url, &len, fp) != -1) {
		// Remove pesky trailing newline
		char *newline = strchr(url, '\n');
		if (newline)
			*newline = 0;
        char *hostname = strtok(url, "/");
        char* pathname = strtok(NULL, "\0");
		match(hostname, pathname, sets);
	}

	fclose(fp);
	free(url);
}
