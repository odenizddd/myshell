#ifndef HISTORY_H
#define HISTORY_H

#include <stdio.h>
#include "parser.h"

#define HISTORY_FILE ".history"

int saveLastExecutedCommand(char *filename, char lastExecutedCommand[MAX_LINE_LENGTH]);
int readLastExecutedCommand(char *filename ,char lastExecutedCommand[MAX_LINE_LENGTH]);

#endif