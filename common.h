#ifndef _COMMON_H
#define _COMMON_H
#include <regex.h> 

// Store for a set of sets
struct set_rec {
    char* val;
    struct set_rec* next;
    struct pat_rec* pat;
};

// Stores for a single pattern
struct pat_rec {
    char* host;
    char* path;
    regex_t host_regex;
    regex_t path_regex;
    struct pat_rec* next;
};

extern int procConf(const char* filename, struct set_rec** sets);
extern int procUrl(const char* filename, struct set_rec* sets);
extern void match(const char* hostname, const char* filename, struct set_rec* sets);
extern unsigned char *loadfile(const char *fname);
extern char *sgets(char *s, int n, const unsigned char **strp);

#endif
