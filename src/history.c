#include "history.h"

/**
 * @brief Save last executed command
 * 
 * @param filename
 * @param lastExecutedCommand 
 * @return int 
 */
int saveLastExecutedCommand(char *filename, char lastExecutedCommand[]) {
    FILE *file = fopen(filename, "w");
    
    if (file == NULL) {
        printf("Can't open %s for write operation.\n", filename);
        return 1;
    }

    fprintf(file, "%s\n", lastExecutedCommand);
    fclose(file);

    return 0;
}

/**
 * @brief Read last executed command.
 * 
 * @param filename 
 * @param lastExecutedCommand 
 * @return int 
 */
int readLastExecutedCommand(char *filename, char lastExecutedCommand[]) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Can't open %s for read operation.\n", filename);
        return 1;
    }

    fgets(lastExecutedCommand, MAX_LINE_LENGTH, file);
    char *nl = strchr(lastExecutedCommand, '\n');
    nl = '\0';

    return 0;
}