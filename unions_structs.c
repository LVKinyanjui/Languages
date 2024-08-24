#include <stdio.h>

typedef union
{
    short count;
    float weight;
    float volume;
} quantity;

typedef struct 
{
    const char* color;
    int gears;
    int height;
} bike;


int main()
{
    // Dot Notation
    quantity q;
    q.weight = 50;
    printf("I have %.1f kilos oranges\n", q.weight);

    // Designated initializers
    bike b = {.gears=5, .color="blue"};
    printf("My %s bike has %i gears\n", b.color, b.gears);
    return 0;
}