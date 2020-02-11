#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

/*
cur is supposed to point to missions for these print functions
*/

void print_station(xmlDocPtr doc, xmlNodePtr cur, char* csvname) {

    std::ofstream info_train(csvname, std::ios_base::out | std::ios_base::app);

    xmlChar *key;
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"stations"))) {
            cur = cur->xmlChildrenNode;
            while (cur != NULL) {
                if ((!xmlStrcmp(cur->name, (const xmlChar*)"name"))) {
                    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                    printf("station: %s\n", key);
                    
                    info_train << "\n,";
                    info_train << key;
                    
                    xmlFree(key);
                }
                cur = cur->next;
            }
            info_train.close();
            return;
        }
        cur = cur->next;
    }
    info_train.close();
    return;
}

void print_stationDates(xmlDocPtr doc, xmlNodePtr cur, char* csvname) {
    
    std::ofstream info_train(csvname, std::ios_base::out | std::ios_base::app);

    xmlChar *key;
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"stationsDates"))) {
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            printf("stationsDates: %s\n", key);

            info_train << ",";
            info_train << key;

            xmlFree(key);
        }
        cur = cur->next;
    }
    info_train.close();
    return;
}

void print_direction(xmlDocPtr doc, xmlNodePtr cur, const xmlChar* attribut, char* csvname) {

    std::ofstream info_train(csvname, std::ios_base::out | std::ios_base::app);

    xmlChar *key;
    cur = cur->xmlChildrenNode;

    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"direction"))) {
            cur = cur->xmlChildrenNode;
            while (cur != NULL) {
                if ((!xmlStrcmp(cur->name, attribut))) {
                    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                    printf("direction->%s: %s\n", attribut, key);
                    
                    info_train << ",";
                    info_train << key;
                    
                    xmlFree(key);
                }
                cur = cur->next;
            }
            info_train.close();
            return;
        }
        cur = cur->next;
    }
    info_train.close();
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

void print_current_train(xmlDocPtr doc, xmlNodePtr cur, char* csvname) {

    // let cur point to missions
    cur = cur->xmlChildrenNode->xmlChildrenNode->xmlChildrenNode->xmlChildrenNode;

    while (cur != NULL && !xmlStrcmp(cur->name, (const xmlChar *)"missions"))
        cur = cur->next;

    if (cur == NULL) return;      

    while (cur != NULL) {
        if (train_arrives(doc, cur)) {
            print_station(doc, cur, csvname);
            print_stationDates(doc, cur, csvname);
            print_direction(doc, cur, (const xmlChar*)"name", csvname);
            print_direction(doc, cur, (const xmlChar*)"sens", csvname);
            return;
        }
        cur = cur->next;
    }
}

int main(int argc, char **argv) {
        
    if (argc != 3) {
        printf("Usage: %s docname csvname\n", argv[0]);
        return (0);
    }

    char* csvname = argv[2];
    char* docname = argv[1];
    xmlDocPtr doc;
    xmlNodePtr cur;

    doc = xmlParseFile(docname);
    
    if (doc == NULL) {
        fprintf(stderr, "document not parsed successfully\n");
        return (0);
    }
    
    cur = xmlDocGetRootElement(doc);

    if (cur == NULL) {
        fprintf(stderr, "empty document\n");
        xmlFreeDoc(doc);
        return (0);
    }

    if (xmlStrcmp(cur->name, (const xmlChar *)"Envelope")) {
        fprintf(stderr, "document of the wrong type\n");
        xmlFreeDoc(doc);
        return (0);
    }

    print_current_train(doc, cur, csvname);

    xmlFreeDoc(doc);
    return (1);
}
