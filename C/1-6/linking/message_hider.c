#include <stdio.h>
#include "encrypt.h"

int main()
{
    int char_length = 80;
    char msg[char_length];
    while (fgets(msg, char_length, stdin)) {
        encrypt(msg);
        printf("%s", msg);
    }
    return 0;
}