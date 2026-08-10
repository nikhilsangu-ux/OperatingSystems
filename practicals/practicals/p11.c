#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int *data = malloc(1000000 * sizeof(int));

    for (int i = 0; i < 1000000; i++)
        data[i] = 10;

    printf("Parent PID = %d\n", getpid());

    pid_t pid = fork();

    if (pid == 0) {
        printf("Child PID = %d\n", getpid());

        for (int i = 0; i < 1000000; i++)
            data[i] = 20;

        printf("Child modified data.\n");

        sleep(5);

        free(data);
        return 0;
    }
    else {
        printf("Parent data = %d\n", data[0]);

        sleep(2);

        printf("Parent data after child modification = %d\n", data[0]);

        wait(NULL);

        free(data);
    }

    return 0;
}