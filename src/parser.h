#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include "alias.h"

#define MAX_TOKEN_COUNT 1024
#define MAX_TOKEN_LENGTH 1024

int tokenize(char tokens[MAX_TOKEN_COUNT][MAX_TOKEN_LENGTH], char *inputString);
void printTokens(char tokens[MAX_TOKEN_COUNT][MAX_TOKEN_LENGTH], int tokenCount);

#endif
