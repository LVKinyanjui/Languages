#include <cstdio>

int absolute_value(int value)
{
    if (value > 0)
        return value;
    else
        return value * -1;
}

int main()
{
    int x = -10;
    printf("The absolute value is %d\n:",
        absolute_value(x));
}
