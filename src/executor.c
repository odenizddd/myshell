#include "executor.h"

/**
 * @brief Handle the fork/exec logic, redirection, and background scheduling.
 * 
 * @param marks 
 * @param tokens 
 * @param tokenCount 
 * @return int 
 */
int execute(struct Marks marks, char tokens[MAX_TOKEN_COUNT][MAX_TOKEN_LENGTH], int tokenCount) {
    if (marks.commandType == EMPTY) {
        return 0;
    } else if (marks.commandType == EXIT) {
        terminateShell();
    } else if (marks.commandType == ALIAS) {
        if (tokenCount == 4) {
            addAlias(tokens[1], tokens[3]);
            return 0;
        }
        return 1;
    } else {  // At this point we know we have a path command
        pid_t pid = fork();
        if (pid == 0) { // Child process
            char *args[MAX_TOKEN_COUNT];
            int argumentCount = tokenCount;
            if (marks.background) {
                argumentCount--;
            }
            if (marks.redirectionType != NONE) {
                argumentCount -=2;
            }
            if (argumentCount <= 0) {
                exit(EXIT_FAILURE);
            }
            for (int i = 0; i < argumentCount; i++) {
                args[i] = tokens[i];
            }
            if (marks.redirectionType == OUTPUT) {
                int fd = open(tokens[argumentCount+1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
                if(fd == -1) {
                    printf("Can't open file.");
                    exit(EXIT_FAILURE);
                }
                if(dup2(fd, STDOUT_FILENO) == -1) {
                    printf("Can't redirect stdout to the file.");
                    exit(EXIT_FAILURE);
                }
                close(fd);
            }
            if (marks.redirectionType == APPEND) {
                int fd = open(tokens[argumentCount+1], O_WRONLY | O_CREAT | O_APPEND, 0666);
                if(fd == -1) {
                    printf("Can't open file.");
                    exit(EXIT_FAILURE);
                }
                if(dup2(fd, STDOUT_FILENO) == -1) {
                    printf("Can't redirect stdout to the file.");
                    exit(EXIT_FAILURE);
                }
                close(fd);
            }
            args[argumentCount] = NULL;
            if (marks.redirectionType != TRIPLE) {
                execvp(args[0], args);
                exit(EXIT_FAILURE);
            } else {
                // Implement triple redirection here.
                int pipe_fd[2];
                if (pipe(pipe_fd) == -1) {
                    printf("Pipe error!\n");
                    exit(EXIT_FAILURE);
                }
                pid_t rpid = fork();
                if (rpid == 0) { // Grandchild
                    close(pipe_fd[0]);
                    dup2(pipe_fd[1], STDOUT_FILENO);
                    close(pipe_fd[1]);
                    int exit_status = execvp(args[0], args); 
                    exit(EXIT_FAILURE);
                } else { // Child
                    close(pipe_fd[1]);
                    char buffer[1024];
                    ssize_t bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));
                    if (bytes_read == -1) {
                        printf("Pipe read error!\n");
                        exit(EXIT_FAILURE);
                    }
                    for (ssize_t i = 0, j = bytes_read-1; i < j; ++i, --j) {
                        char temp = buffer[i];
                        buffer[i] = buffer[j];
                        buffer[j] = temp;
                    }
                    int fd = open(tokens[argumentCount+1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
                    if (fd == -1) {
                        printf("Can't open file.\n");
                        exit(EXIT_FAILURE);
                    }
                    ssize_t bytes_written = write(fd, buffer, bytes_read);
                    if (bytes_written == -1) {
                        printf("Write error!\n");
                        exit(EXIT_FAILURE);
                    }
                    close(fd);
                    close(pipe_fd[0]);
                    exit(EXIT_SUCCESS);
                }
            }
        } else { // parent process
            if (!marks.background) {
                int exit_status;
                waitpid(pid, &exit_status, 0);
                if (exit_status != 0) {
                    printf("\33[31mChild process exited with an error.\33[0m\n");
                    return EXIT_FAILURE;
                }
                return EXIT_SUCCESS;
            }
        }
    }
}