#include "shell_init.h"

/**
 * @brief Interrupt signal handler
 * 
 */
static void _handleInterrupt() {
    terminateShell();
}

/**
 * @brief Shell initialization code.
 * 
 */
void initializeShell() {
    struct sigaction sa;
    sa.sa_handler = _handleInterrupt;
    sa.sa_flags = SA_RESTART; // Restart system calls if interrupted by handler

    // Register the signal handler using sigaction
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Failed to register signal handler");
        exit(EXIT_FAILURE);
    }
    
    char *currentPath = getenv("PATH");
    char newPath[MAX_LINE_LENGTH];
    snprintf(newPath, sizeof(newPath), ".:%s", currentPath);

    if (setenv("PATH", newPath, 1) != 0) {
        printf("Error setting path.");
        exit(EXIT_FAILURE);
    }

    loadAliases(ALIAS_FILE);
}

/**
 * @brief Code to be run right before shell exits.
 * 
 */
void terminateShell() {
    saveAliases(ALIAS_FILE);
    exit(EXIT_SUCCESS);
}