#include <stdio.h>
#include <pthread.h>

// Thread functions accept only one void* type parameter
// long values can be stored in void pointers
// because they are the same size.
void* do_stuff(void* param)
{
    long thread_no = (long)param;
    printf("Thread number %ld\n", thread_no);
    return (void*)(thread_no + 1);
}

int main()
{
    pthread_t threads[20];

    long t;
    for (t = 0; t < 3; t++) {
        // Convert the long t value to a void pointer.
        pthread_create(&threads[t], NULL, do_stuff, (void*)t);
    }

    void* result;
    for (t = 0; t < 3; t++) {
        pthread_join(threads[t], &result);
        //Convert the return value to a long before using it.
        printf("Thread %ld returned %ld\n", t, (long)result);
    }
    return 0;
}
