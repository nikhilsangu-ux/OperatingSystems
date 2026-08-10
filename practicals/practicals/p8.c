#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int signal)
{
    if (signal == SIGINT)
        printf("\nSIGINT received\n");

    else if (signal == SIGTERM)
        printf("\nSIGTERM received\n");

    else if (signal == SIGUSR1)
        printf("\nSIGUSR1 received\n");
}

int main()
{
    signal(SIGINT, handler);
    signal(SIGTERM, handler);
    signal(SIGUSR1, handler);

    printf("PID = %d\n", getpid());

    while (1) {
        printf("Running...\n");
        sleep(2);
    }

    return 0;
}