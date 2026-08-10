#include <stdio.h>
#include <pthread.h>

#define THREADS 4
#define ITERATIONS 1000000

long counter = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *increment(void *arg)
{
    for (int i = 0; i < ITERATIONS; i++) {
        pthread_mutex_lock(&mutex);

        counter++;

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main()
{
    pthread_t threads[THREADS];

    for (int i = 0; i < THREADS; i++)
        pthread_create(&threads[i], NULL, increment, NULL);

    for (int i = 0; i < THREADS; i++)
        pthread_join(threads[i], NULL);

    printf("Expected value = %d\n", THREADS * ITERATIONS);
    printf("Actual value   = %ld\n", counter);

    pthread_mutex_destroy(&mutex);

    return 0;
}