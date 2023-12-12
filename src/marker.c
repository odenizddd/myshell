#include "marker.h"

/**
 * @brief Make sense of tokens.
 * 
 * @param mark 
 * @param tokens 
 */
void mark(struct Marks *marks, char tokens[MAX_TOKEN_COUNT][MAX_TOKEN_LENGTH], int tokenCount) {

    // Determine the command type.
    if (tokenCount == 0) {
        marks->commandType = EMPTY;
        return;
    } else if (strcmp(tokens[0], "exit") == 0) {
        marks->commandType = EXIT;
    } else if (strcmp(tokens[0], "alias") == 0) {
        marks->commandType = ALIAS;
    } else {
        marks->commandType = PATH;
    }

    // Determine if this is a background process.
    if (strcmp(tokens[tokenCount-1], "&") == 0) {
        marks->background = 1;
    } else {
        marks->background = 0;
    }

    // Determine redirection type.
    int redirectionIndex = tokenCount - 2;
    if (marks->background) {
        redirectionIndex--;
    }
    if (redirectionIndex > 0) {
        if (strcmp(tokens[redirectionIndex], ">") == 0) {
            marks->redirectionType = OUTPUT;
        } else if (strcmp(tokens[redirectionIndex], ">>") == 0) {
            marks->redirectionType = APPEND;
        } else if (strcmp(tokens[redirectionIndex], ">>>") == 0) {
            marks->redirectionType = TRIPLE;
        } else {
            marks->redirectionType = NONE;
        }
    }
}

/**
 * @brief Brief explanation of the mark object.
 * 
 * @param mark 
 */
void summerizeMark(struct Marks* marks) {
    printf("CommandType: %d\n", marks->commandType);
    printf("RedirectionType: %d\n", marks->redirectionType);
    printf("Background: %d\n", marks->background);
}