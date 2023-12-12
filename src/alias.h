#ifndef ALIAS_H
#define ALIAS_H

#include <string.h>
#include <stdio.h>

#define MAX_ALIAS_COUNT 1024
#define ALIAS_BUFFER_SIZE 1024
#define COMMAND_BUFFER_SIZE 1024
#define MAX_LINE_LENGTH 1024
#define ALIAS_FILE ".aliases"

struct Alias {
    char aliasName[ALIAS_BUFFER_SIZE];
    char command[COMMAND_BUFFER_SIZE];
};

int loadAliases(char * );
int saveAliases(char * );
void addAlias(char * , char * );
void printAliasList();
char * findAlias(char * );

#endif
