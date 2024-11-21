#include <cstddef>
#include <cstdio>

template<typename T>
T mean(const T* values, size_t length) {
    T result{};
    for(size_t i{}; i<length; i++) {
        result += values[i];
    }
    return result / length;
}

int main() {
    const float nums_f[] {1.0, 2.0, 3.0};
    // With template parameter float, for demonstration
    const auto result1 = mean<float>(nums_f, 3);
    printf("float:  %f\n", result1);

    const int nums_i[] {2, 3, 5, 6, 7};
    // Without template parameter int,
    // Compiler uses template type deduction
    const auto result2 = mean(nums_i, 5);
    printf("integer:  %d\n", result2);

    return 0;
}
