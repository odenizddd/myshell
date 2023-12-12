#ifndef MARKER_H
#define MARKER_H

#include "parser.h"

enum CommandType {
    EMPTY,
    EXIT,
    ALIAS,
    PATH
};

enum RedirectionType {
    NONE,
    OUTPUT,
    APPEND,
    TRIPLE
};

struct Marks {
    enum CommandType commandType;
    enum RedirectionType redirectionType;
    int background;
};

void mark(struct Marks *marks, char tokens[MAX_TOKEN_COUNT][MAX_TOKEN_LENGTH], int tokenCount);
void summerizeMark(struct Marks *marks);

#endif
