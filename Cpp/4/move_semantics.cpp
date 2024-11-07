#include <cstdio>
#include <utility>  // for std::move

struct MoveableClass {
    MoveableClass(const char* name) {
        this->name = name;
    }

    // Move Constructor
    MoveableClass(MoveableClass&& other) noexcept {
        this->name = other.name;
    }

    // Copy Constructor
    MoveableClass(MoveableClass& other) noexcept {
        this->name = other.name;
    }

    // Move assignment
    MoveableClass& operator=(MoveableClass&& other) noexcept {
        if (this == &other) return *this;
        this->name = other.name;
        return *this;
    }

    // Copy assignment
    MoveableClass& operator=(MoveableClass& other) noexcept {
        if (this == &other) return *this;
        this->name = other.name;
        return *this;
    }

    void print() {
        printf("%s\n", this->name);
    }

    const char* name {};
};

int main() {
    MoveableClass mc { "My moveable class"};
    mc.print();

    MoveableClass mc_moved {"My moved class"};

    mc_moved = std::move(mc);
    mc_moved.print();   // Will print identical input to the moved from class

    return 0;
}
