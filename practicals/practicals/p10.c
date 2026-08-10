#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *a;
    int *b;

    a = malloc(5 * sizeof(int));

    if (a == NULL)
        return 1;

    for (int i = 0; i < 5; i++)
        a[i] = i;

    b = calloc(5, sizeof(int));

    if (b == NULL) {
        free(a);
        return 1;
    }

    a = realloc(a, 10 * sizeof(int));

    if (a == NULL) {
        free(b);
        return 1;
    }

    free(a);
    free(b);

    return 0;
}