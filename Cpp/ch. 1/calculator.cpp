#include <cstdio>

typedef enum class Operation {
    Add, Subtract, Multiply, Divide
} Operation;

struct Calculator {
    Calculator(Operation operation_in) {
        operation = operation_in;
    }

    int calculate(int a, int b) {
        switch (operation) {
            case Operation::Add: {
                return a + b;
            }
            case Operation::Subtract: {
                return a - b;
            }
            case Operation::Multiply: {
                return  a * b;
            }
            case Operation::Divide: {
                return a / b;
                //TODO:     Handle zero division exception
            }
            default: {
                puts("Operation is not supported!");
                return 0;
            }
        }
    }
    Operation operation;
};

int main() {
    Calculator calculator = { Operation::Multiply };
    int result = calculator.calculate(17, 16);
    printf("Operation result:    %d\n", result);
    return 0;
}
