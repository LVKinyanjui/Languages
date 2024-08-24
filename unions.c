#include <stdio.h>

typedef union
{
    short count;
    float weight;
    float volume;
} quantity;

int main()
{
    quantity q;
    q.weight = 50;
    printf("I have %.1f kilos oranges", q.weight);
    return 0;
}