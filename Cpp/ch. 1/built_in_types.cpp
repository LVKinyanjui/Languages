#include <cstddef>
#include <cstdio>
#include <cstdint>
#include <iterator>

int main() {
    int8_t x = 0b010000000;
    int16_t y = 0xaf85;
    int32_t z = 0xff88ae3b;
    printf("My integer values are:\n %d\n, %d\n, %d\n",
        x, y, z);

    size_t size_c = sizeof(char);
    printf("char size: %zd\n", size_c);
    size_t size_l = sizeof(long);
    printf("long size: %zd\n", size_l);


    int my_array[] = {1, 2, 3};
    puts("My array elements are:\n");

    // Range based loop
    for(int element: my_array) {
        printf("%d\n", element);
    }


    int my_other_array[] = {4, 5, 6};
    // Better size calculations for containers with a size method
    size_t array_length = std::size(my_other_array);
    puts("My other array elements are:\n");

    // Iterator based loop
    for(int i=0; i < array_length; i++) {
        printf("%d\n", my_other_array[i]);
    }
    return 0;
}
