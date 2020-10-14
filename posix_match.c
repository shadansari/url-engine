#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include "common.h"

char msgbuf[100];

static int regex_match(regex_t *regex, const char *str) {
    int reti = regexec(regex, str, 0, NULL, 0);
    if (!reti) {
        return 0;
    } else if (reti == REG_NOMATCH) {
        return 1;
    }
    else {
        regerror(reti, regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }
}

void match(const char* hostname, const char* pathname, struct set_rec* sets) {
	//printf("host:%s path:%s\n", hostname, pathname);
    for (struct set_rec* s = sets; s != NULL; s = s->next) {
        for (struct pat_rec* p = s->pat; p != NULL; p = p->next) {
            if (hostname != NULL) {
                if (!regex_match(&p->host_regex, hostname)) {
                    if (pathname != NULL) {
                        if (!regex_match(&p->path_regex, pathname)) {
                            printf("Match %s/%s -> %s/%s\n", hostname, pathname, p->host, p->path);
                        }
                    } else {
                        printf("Match %s -> %s%s\n", hostname, p->host, p->path?"/p->path":"");
                    }
                }
            }
        }
    }
    return;
}
