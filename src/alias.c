#include "alias.h"

struct Alias aliasList[MAX_ALIAS_COUNT];
int aliasCount = 0;

/**
 * @brief Load the aliases from  a file into a buffer in the memory.
 * 
 * @param input_file 
 * @return int 
 */
int loadAliases(char * input_file) {
    FILE * file = fopen(input_file, "r");

    if (file == NULL) {
        //printf("Can't open %s for read operation.\n", input_file);
        return 1;
    }

    char input_buffer[MAX_LINE_LENGTH];
    char aliasName[ALIAS_BUFFER_SIZE];
    char commandName[COMMAND_BUFFER_SIZE];
    while (fgets(input_buffer, sizeof(input_buffer), file) != NULL)
    {
        char * nl = strchr(input_buffer, '\n');
        if (nl != NULL) {*nl = '\0';}
        char * aliasP = strtok(input_buffer, "=");
        char * commandP = strtok(NULL, "=");
        if (aliasP != NULL && commandP != NULL) {
            strcpy(aliasName, aliasP);
            strcpy(commandName, commandP);
            addAlias(aliasName, commandName);
        }
        /*
        if ("%d", sscanf(input_buffer, "%1024[^= ]=%s", aliasName, commandName) == 2) {
            addAlias(aliasName, commandName);
        }
        */
            
    }
    return 0;
}

/**
 * @brief Saves aliases from the memory into a file.
 * 
 * @param output_file 
 * @return int 
 */
int saveAliases(char * output_file) {
    FILE * file = fopen(output_file, "w");

    if (file == NULL) {
        printf("Can't open %s for write operation.\n", output_file);
        return 1;
    }

    for (int i = 0; i < aliasCount ; i++) {
        fprintf(file, "%s=%s\n", aliasList[i].aliasName, aliasList[i].command);
    }

    fclose(file);
    return 0;
}

/**
 * @brief Adds an alias to the current alias list in the memory.
 * 
 * @param aliasName 
 * @param commandName 
 */
void addAlias(char * aliasName, char * commandName) {
    strcpy(aliasList[aliasCount].aliasName, aliasName);
    strcpy(aliasList[aliasCount].command, commandName);
    aliasCount += 1;
}

/**
 * @brief Prints the list of aliases.
 * 
 */
void printAliasList() {
    printf("Aliases: %d\n", aliasCount);
    for (int i = 0; i < aliasCount; i++) {
        printf("Alias[%d]: %s = %s\n", i, aliasList[i].aliasName, aliasList[i].command);
    }
}

/**
 * @brief Returns the actual command for an alias, NULL if the
 * the alias is non-existent.
 * 
 * @param aliasName 
 * @return char* 
 */
char * findAlias(char * aliasName) {
    for (int i = aliasCount-1; i >= 0; i--) {
        if (strcmp(aliasList[i].aliasName, aliasName) == 0) {
            return aliasList[i].command;
        }
    }
    return NULL;
}

