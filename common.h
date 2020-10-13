#ifndef _COMMON_H
#define _COMMON_H

// Store for a set of sets
struct set_rec {
    char* val;
    struct set_rec* next;
    struct pat_rec* pat;
};

// Stores for a single pattern
struct pat_rec {
    char* hostname;
    char* pathname;
    struct pat_rec* next;
};

extern int procConf(const char* filename, struct set_rec** sets);
extern void procUrl(const char* filename, struct set_rec* sets);
extern void match(const char* hostname, const char* filename, struct set_rec* sets);

#endif
