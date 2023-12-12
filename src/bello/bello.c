#include "bello.h"

/**
 * @brief Belloooooo!
 * 
 */
void bello() {
    // print username
    char * username = getenv("USER");
    printf("%s\n", username);

    // print hostname
    char hostname[1024];
    gethostname(hostname, sizeof(hostname));
    char *dotLocal = strstr(hostname, ".local");
    if (dotLocal != NULL) {
        *dotLocal = '\0';
    }
    printf("%s\n", hostname);

    // print the last executed command
    char lastExecutedCommand[1024];
    readLastExecutedCommand(HISTORY_FILE, lastExecutedCommand);
    printf("%s", lastExecutedCommand);

    // print tty
    char * tty = ttyname(STDIN_FILENO);
    printf("%s\n", tty);

    // print current shell name
    pid_t pid = getppid();
    int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_PID, pid };
    struct kinfo_proc info;
    size_t size = sizeof(info);

    if (sysctl(mib, 4, &info, &size, NULL, 0) == 0) {
        printf("%s\n", info.kp_proc.p_comm);
    } else {
        perror("Error getting process name");
    }

    // print home location
    printf("%s\n", getenv("HOME"));

    // print current time and date
    time_t t;
    struct tm * time_info;
    time(&t);
    time_info = localtime(&t);
    printf("%s", asctime(time_info));

    // print the number of processes being executed
    mib[2] = KERN_PROC_ALL;
    mib[3] = 0;
    sysctl(mib, 4, NULL, &size, NULL, 0);
    printf("%d\n", size / sizeof(struct kinfo_proc));

}  

int main () {
    bello(); 
    return 0;
}