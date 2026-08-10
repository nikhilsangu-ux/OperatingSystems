#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t children[3];

    for (int i = 0; i < 3; i++) {
        children[i] = fork();

        if (children[i] < 0) {
            perror("fork");
            exit(1);
        }

        if (children[i] == 0) {
            printf("Child %d: PID = %d\n", i + 1, getpid());
            sleep(i + 1);
            exit(i + 1);
        }
    }

    printf("Parent PID = %d\n", getpid());

    wait(NULL);

    printf("One child completed using wait().\n");

    for (int i = 0; i < 3; i++) {
        int status;

        if (waitpid(children[i], &status, 0) > 0) {
            printf("Child PID %d completed.\n", children[i]);
        }
    }

    return 0;
}