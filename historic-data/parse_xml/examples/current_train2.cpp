#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

/*
cur is supposed to point to missions for these print functions
*/

void print_stationDates(xmlDocPtr doc, xmlNodePtr cur) {
    xmlChar *key;
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"stationsDates"))) {
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            printf("stationsDates: %s\n", key);
            xmlFree(key);
        }
        cur = cur->next;
    }
    return;
}

void print_direction(xmlDocPtr doc, xmlNodePtr cur) {

    xmlChar *key_name;
    xmlChar *key_sens;
    cur = cur->xmlChildrenNode;
    
    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"direction"))) {
            cur = cur->xmlChildrenNode;
            while (cur != NULL) {
                if ((!xmlStrcmp(cur->name, (const xmlChar *)"name"))) {
                    key_name = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                    printf("direction->name: %s\n", key_name);
                    xmlFree(key_name);
                }
                if ((!xmlStrcmp(cur->name, (const xmlChar *)"sens"))) {
                    key_sens = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                    printf("direction->sens: %s\n", key_sens);
                    xmlFree(key_sens);
                }
                cur = cur->next;
            }
            return;
        }
        cur = cur->next;
    }
    return;
}

bool train_arrives(xmlDocPtr doc, xmlNodePtr cur) {
    bool res;
    xmlChar *key;
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"stationsMessages"))) {
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            res = (!xmlStrcmp(key, (const xmlChar *)"Train à quai"));
            xmlFree(key);
            
            return res;
        }
        cur = cur->next;
    }
}

int main(int argc, char **argv) {

    char *docname;
    xmlDocPtr doc;
    xmlNodePtr cur;
        
    if (argc <= 1) {
        printf("Usage: %s docname\n", argv[0]);
        return (0);
    }

    docname = argv[1];

    doc = xmlParseFile(docname);
    
    if (doc == NULL) {
        fprintf(stderr, "document not parsed successfully. \n");
        return (0);
    }
    
    cur = xmlDocGetRootElement(doc);

    if (cur == NULL) {
        fprintf(stderr, "empty document\n");
        xmlFreeDoc(doc);
        return (0);
    }
    
    if (xmlStrcmp(cur->name, (const xmlChar *)"missions")) {
        fprintf(stderr, "document of the wrong type, root node != missions");
        xmlFreeDoc(doc);
        return (0);
    }

    if (train_arrives(doc, cur)) {
        print_stationDates(doc, cur);
        cur = xmlDocGetRootElement(doc);
        print_direction(doc, cur);
    }

    xmlFreeDoc(doc);
    return (1);
}
