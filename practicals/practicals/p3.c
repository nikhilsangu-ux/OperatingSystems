#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf("Child Process\n");
        printf("PID  = %d\n", getpid());
        printf("PPID = %d\n", getppid());

        printf("Child is running.\n");

        sleep(5);

        printf("Child is terminating.\n");
        exit(0);
    }
    else {
        printf("Parent Process\n");
        printf("PID  = %d\n", getpid());
        printf("PPID = %d\n", getppid());

        sleep(2);

        wait(NULL);

        printf("Parent: Child terminated.\n");
    }

    return 0;
}