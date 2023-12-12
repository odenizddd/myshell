#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "marker.h"
#include <stdio.h>
#include "shell_init.h"
#include <unistd.h>
#include <fcntl.h>

int execute(struct Marks marks, char tokens[MAX_TOKEN_COUNT][MAX_TOKEN_LENGTH], int tokenCount);

#endif
