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
    char* val;
    struct pat_rec* next;
};

extern int streamFile(const char *filename, struct set_rec** sets);

#endif
