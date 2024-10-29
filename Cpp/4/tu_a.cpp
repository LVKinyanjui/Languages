#include <cstdio>
extern int available;
void some_fn() {
    available = 0;
    printf("Available:  %d", available);
}
