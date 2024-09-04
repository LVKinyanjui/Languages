#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int compare(const void *score_a, const void *score_b)
{
    int a = *(int*)score_a;
    int b = *(int*)score_b;

    return a - b;
}

int compare_desc(const void *score_a, const void *score_b)
{
    int a = *(int*)score_a;
    int b = *(int*)score_b;

    return b - a;
}

int main ()
{
    int scores[] = {543,323,32,554,11,3,112};
    int element_size = sizeof(scores[0]);
    int length = sizeof(scores) / element_size; // Calculate length

    qsort(&scores, length, element_size, compare_desc);

    puts("Here are the sorted elements of the array ...");
    for(int i=0; i < length; i++) {
        printf("Element %d: %d\n", i, scores[i]);
    }    
    return 0;
}