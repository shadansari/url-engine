#include <stdio.h>
#include "common.h"

void match(const char* hostname, const char* pathname, struct set_rec* sets) {
	printf("host:%s path:%s\n", hostname, pathname);
    for (struct set_rec* s = sets; s != NULL; s = s->next) {
        for (struct pat_rec* p = s->pat; p != NULL; p = p->next) {
        }
    }
    return;
}
