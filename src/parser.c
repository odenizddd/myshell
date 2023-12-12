#include "parser.h"

/**
 * @brief Populates the token buffer with the tokens extracted from the input string.
 * 
 * @param tokens
 * @param inputString
 * @param tokenCount This is where the first token is put.
 * @return int 
 */
static int _tokenize(char tokens[MAX_TOKEN_COUNT][MAX_TOKEN_LENGTH], char *inputString, int tokenCount) {
    int length = strlen(inputString);
    if (length == 0) {
        return tokenCount;
    }

    int tokenIndex = 0;
    int insideQuotes = 0;

    for (int i = 0; i < length; i++) {
        if (inputString[i] == '"') {
            insideQuotes = !insideQuotes;
        } else if(inputString[i] != ' ' || insideQuotes) {
            tokens[tokenCount][tokenIndex++] = inputString[i];
        } else if (tokenIndex > 0){
            tokens[tokenCount++][tokenIndex] = '\0';
            tokenIndex = 0;
        }
    }

    if (tokenIndex > 0) {
        tokens[tokenCount++][tokenIndex] = '\0';
    }

    return tokenCount;
}

/**
 * @brief Populates the token buffer buffer with the tokens extracted from
 * the input string after expanding aliases.
 * 
 * @param tokens 
 * @param inputString 
 * @return int 
 */
int tokenize(char tokens[MAX_TOKEN_COUNT][MAX_TOKEN_LENGTH], char *inputString) {
    int tokenCount = _tokenize(tokens, inputString, 0);
    if (tokenCount == 0) {
        return 0;
    }
    char *command = findAlias(tokens[0]);
    if (command != NULL) {
        char *aliasPos = strstr(inputString, tokens[0]);
        int aliasLen = strlen(tokens[0]);
        tokenCount = _tokenize(tokens, command, 0);
        tokenCount = _tokenize(tokens, aliasPos+aliasLen, tokenCount);
    }
    return tokenCount; // TODO: Return what actually need to be returned.
}

/**
 * @brief Print tokens in a token array.
 * 
 * @param tokens 
 */
void printTokens(char tokens[MAX_TOKEN_COUNT][MAX_TOKEN_LENGTH], int tokenCount) {
    printf("Tokens: %d\n", tokenCount);
    for (int i = 0; i < tokenCount; i++) {
        printf("Token[%d] = %s\n", i, tokens[i]);
    }
}