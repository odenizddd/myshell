#include "parser.h"
#include "marker.h"
#include "alias.h"
#include "shell_init.h"
#include "executor.h"
#include "marker.h"
#include "history.h"

int main() {

    // init
    initializeShell();

    char *username = getenv("USER");
    char hostname[MAX_LINE_LENGTH];
    gethostname(hostname, sizeof(hostname));
    char *dotLocal = strstr(hostname, ".local");
    if (dotLocal != NULL) {
        *dotLocal = '\0';
    }
    char cwd[MAX_LINE_LENGTH];
    getcwd(cwd, sizeof(cwd));
    

    char inputString[MAX_LINE_LENGTH];
    // in a loop
    while (1) {
        printf("%s@%s %s --- ", username, hostname, cwd);
        fgets(inputString, MAX_LINE_LENGTH, stdin);
        char *EOL = strchr(inputString, '\n');
        *EOL = '\0';

        char tokens[MAX_TOKEN_COUNT][MAX_TOKEN_LENGTH];
        
        int tokenCount = tokenize(tokens, inputString);
        /*
        printf("\n");
        printTokens(tokens, tokenCount);
        */

        struct Marks marks = {.background=0, .commandType=EMPTY, .redirectionType=NONE};
        mark(&marks, tokens, tokenCount);
        /*
        printf("\n");
        summerizeMark(&marks);
        printf("\n");
        */

        int status = execute(marks, tokens, tokenCount);
        if (!status) {
            //printf("\033[32mSuccessful execution.\033[0m\n");
            if (marks.commandType != EMPTY) {
                saveLastExecutedCommand(HISTORY_FILE, inputString);
            }
        } else {
            //printf("\033[31mError.\033[0m\n");
        }
    }
    

    // exit
    terminateShell();

    // playground

    return 0;
}