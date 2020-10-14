#include <string.h>
#include <libxml/xmlreader.h>
#include <assert.h>
#include "common.h"

// FIXME - hardcoded limit for hostname or pathname
#define MAXURLSIZE 4096
char regex_buf[MAXURLSIZE];

static void make_regex(char* str, regex_t* regex) {
    char *p, *q;

    if (!str)
        return;

    int i = 0, len = strlen(str);

    assert(strlen(str) < MAXURLSIZE);
    q = regex_buf;
    *q++ = '^';
    for (p=str; i<len; i++,p++) {
        if (*p == '*') {
            strncpy(q, "[[:graph:]]*", 12);
            q += 12;
        } else if (*p == '.') {
            strncpy(q, "[.]", 3);
            q += 3;
        } else {
            *q = *p;
            q++;
        }
    }
    *q++ = '$';
    *q = '\0';

    int reti = regcomp(regex, regex_buf, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    //printf("%s -> %s\n", str, regex_buf);
}

static void processNode(xmlTextReaderPtr reader, struct set_rec** sets) {
    xmlChar *name;
    int node_type;
    static struct set_rec* curr_set = NULL;

    name = xmlTextReaderName(reader);
    node_type = xmlTextReaderNodeType(reader);

    if ((node_type == 1) && (!strcmp((const char*)name, "set"))) {
        struct set_rec* s = malloc(sizeof(struct set_rec));
        s->val = (char *)xmlTextReaderGetAttribute(reader, BAD_CAST("id"));
        s->next = *sets;
        *sets = s;
        curr_set = s;

    } else if (node_type == 3) {
        struct pat_rec* p = malloc(sizeof(struct pat_rec));
        char* url = (char *)xmlTextReaderValue(reader);
        p->host = strtok(url, "/");
        make_regex(p->host, &p->host_regex);
        p->path = strtok(NULL, "\0");
        make_regex(p->path, &p->path_regex);
        p->next = curr_set->pat;
        curr_set->pat = p;
    }

    xmlFree(name);
}

int procConf(const char *filename, struct set_rec** sets) {
    xmlTextReaderPtr reader;
    int ret;

    reader = xmlNewTextReaderFilename(filename);
    if (reader != NULL) {
        ret = xmlTextReaderRead(reader);
        while (ret == 1) {
            processNode(reader, sets);
            ret = xmlTextReaderRead(reader);
        }
        xmlFreeTextReader(reader);
        if (ret != 0) {
            printf("%s : failed to parse\n", filename);
        }
    } else {
        printf("Unable to open %s\n", filename);
        ret = 1;
    }

    return ret;
}
