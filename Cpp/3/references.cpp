#include <cstdio>

int main() {
    int original = 100;
    int& original_ref = original;
    printf("Original:   %d\n", original);
    printf("Reference:   %d\n", original_ref);

    int new_value = 200;
    // Assign new value to original which is what original_ref points to
    original_ref = new_value;
    printf("New Value:   %d\n", new_value);
    // See that the value of original has changed
    printf("Original:   %d\n", original);

    return 0;
}
