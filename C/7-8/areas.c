#include <stdio.h>
#include <stdlib.h>

//TODO: Use a dynamic array to read from a txt with rectangle data

typedef struct 
{
    int width;
    int height;
} rectangle;

int compare(const void *item_a, const void *item_b)
{
    rectangle a = *(rectangle*)item_a;
    rectangle b = *(rectangle*)item_b;

    int area_a = a.height * a.width;
    int area_b = b.height * b.width;

    return area_a - area_b;
}

int main()
{

    rectangle rects[] = {
        {2, 5},
        {7, 8},
        {3, 9},
        {4, 8},
        {2, 6},
    };

    int element_size = sizeof(rects[0]);
    int array_length = sizeof(rects) / element_size; // Calculate array_length

    qsort(&rects, array_length, element_size, compare);

    for(int i=0; i < array_length; i++) {
        printf("Sorted Areas: %d\n", 
            rects[i].width * rects[i].height);
    }    

    return 0;
}