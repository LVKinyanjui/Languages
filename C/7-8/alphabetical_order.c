#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_names(const void* a, const void* b)
{
    char** sa = (char**)a;
    char** sb = (char**)b;
    return strcmp(*sa, *sb);

}

int main()
{
    const char *names[] = {"Billy", "Stephanie", "Paul", "Justin", "Leonard", "Richard", "Vincent"};

    int element_size = sizeof(names[0]);
    int array_length = sizeof(names) / element_size;

    qsort(names, array_length, element_size, compare_names);

    for(int i=0; i < array_length; i++) {
        printf("%s\n", names[i]);
    }
    return 0;
}