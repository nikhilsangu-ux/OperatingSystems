#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int src, dest;
    char buffer[1024];
    ssize_t bytes;

    if (argc != 3) {
        printf("Usage: %s source destination\n", argv[0]);
        return 1;
    }

    src = open(argv[1], O_RDONLY);

    if (src < 0) {
        perror("Source file");
        return 1;
    }

    dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (dest < 0) {
        perror("Destination file");
        close(src);
        return 1;
    }

    while ((bytes = read(src, buffer, sizeof(buffer))) > 0) {
        write(dest, buffer, bytes);
    }

    close(src);
    close(dest);

    printf("File copied successfully.\n");

    return 0;
}