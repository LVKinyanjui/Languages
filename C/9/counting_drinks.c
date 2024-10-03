#include <stdio.h>
#include <pthread.h>

pthread_mutex_t a_lock = PTHREAD_MUTEX_INITIALIZER;

int beers = 2000000;  // Global variable shared by all threads

pthread_mutex_t beers_lock = PTHREAD_MUTEX_INITIALIZER;

void* drink_lots(void *a)
{
    int i;
    pthread_mutex_lock(&beers_lock);
    for (i = 0; i < 100000; i++) {
    beers = beers - 1;
    }
    pthread_mutex_unlock(&beers_lock);
    printf("beers = %i\n", beers);
    return NULL;
}

int main() {
    // Create 20 threads
    pthread_t threads[20];

    printf("%d bottles of beer on the wall\n%d bottles of beer\n", beers, beers);

    for (int t = 0; t < 20; t++) {
        if (pthread_create(&threads[t], NULL, drink_lots, NULL) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int t = 0; t < 20; t++) {
        if (pthread_join(threads[t], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    // Print the final number of beers
    printf("There are now %d bottles of beer on the wall\n", beers);

    return 0;
}
