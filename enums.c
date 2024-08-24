#include <stdio.h>

typedef enum {
    COUNT, POUNDS, PINTS
} unit_of_measure;

typedef union 
{
    short count;
    float weight;
    float volume
} quantity;


int main()
{

    return 0;
}