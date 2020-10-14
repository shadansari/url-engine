#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include "common.h"

char msgbuf[100];

static inline int regex_match(regex_t *regex, const char *str) {
    int reti = regexec(regex, str, 0, NULL, 0);
    if (!reti) {
        return 0;
    } else if (reti == REG_NOMATCH) {
        return 1;
    }
    else {
        regerror(reti, regex, msgbuf, sizeof(msgbuf));
        printf("Regex match failed: %s\n", msgbuf);
        exit(1);
    }
}

void match(const char* host, const char* path, struct set_rec* sets) {
    printf("URL:");
    path ? printf("%s/%s", host, path) : printf("%s", host);
    for (struct set_rec* s = sets; s != NULL; s = s->next) {
        for (struct pat_rec* p = s->pat; p != NULL; p = p->next) {
            if (host) {
                if (!regex_match(&p->host_regex, host)
                        && (((path) && (!regex_match(&p->path_regex, path)))
                            || (!path))) {
                            printf(";Set:%s:Pattern:", s->val);
                            path ? printf("%s/%s", host, path) : printf("%s", host);
                }
            }
        }
    }
    printf("\n");
    return;
}
