#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    char command[100];
    char *args[20];
    int i = 0;

    printf("Enter Linux command: ");
    fgets(command, sizeof(command), stdin);

    command[strcspn(command, "\n")] = '\0';

    char *token = strtok(command, " ");

    while (token != NULL && i < 19) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }

    args[i] = NULL;

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

        execvp(args[0], args);

        perror("execvp");
        exit(1);
    }
    else {
        printf("Parent PID: %d\n", getpid());
        wait(NULL);
        printf("Child process completed.\n");
    }

    return 0;
}