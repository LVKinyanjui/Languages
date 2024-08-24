#include <stdio.h>

typedef union
{
    short count;
    float weight;
    float volume;
} quantity;

int main()
{
    quantity q = {3};
    printf("I have %i oranges", q.count);
    return 0;
}