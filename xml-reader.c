#include <libxml/xmlreader.h>

static void processNode(xmlTextReaderPtr reader) {
    xmlChar *name, *value;

    name = xmlTextReaderName(reader);
    if (name == NULL)
        name = xmlStrdup(BAD_CAST "--");
    value = xmlTextReaderValue(reader);

    printf("%d %d %s %d",
            xmlTextReaderDepth(reader),
            xmlTextReaderNodeType(reader),
            name,
            xmlTextReaderIsEmptyElement(reader));
    xmlFree(name);
    if (value == NULL)
        printf("\n");
    else {
        printf(" %s\n", value);
        xmlFree(value);
    }
}

int streamFile(const char *filename) {
    xmlTextReaderPtr reader;
    int ret;

    reader = xmlNewTextReaderFilename(filename);
    if (reader != NULL) {
        ret = xmlTextReaderRead(reader);
        while (ret == 1) {
            processNode(reader);
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
