#include <string.h>
#include <libxml/xmlreader.h>
#include "common.h"

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
        p->hostname = strtok(url, "/");
        p->pathname = strtok(NULL, "\0");
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
