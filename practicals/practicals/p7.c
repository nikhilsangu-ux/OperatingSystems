#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    char buffer[100];

    mkfifo("myfifo", 0666);

    int fd = open("myfifo", O_RDONLY);

    while (read(fd, buffer, sizeof(buffer)) > 0) {
        printf("Server received: %s\n", buffer);
    }

    close(fd);

    return 0;
}