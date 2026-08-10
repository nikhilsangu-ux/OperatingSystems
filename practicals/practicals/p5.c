#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int pipefd[2];
    pid_t pid;

    pipe(pipefd);

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        close(pipefd[1]);

        char buffer[100];
        int n;

        while ((n = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[n] = '\0';
            printf("Consumer received: %s", buffer);
        }

        close(pipefd[0]);
    }
    else {
        close(pipefd[0]);

        for (int i = 1; i <= 5; i++) {
            char message[100];

            sprintf(message, "Data %d\n", i);
            write(pipefd[1], message, strlen(message));
        }

        close(pipefd[1]);
        wait(NULL);
    }

    return 0;
}