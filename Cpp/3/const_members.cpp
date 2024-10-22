#include <cstdio>

struct Surname {
    Surname(const char* name)
    : name { name } {   // MEMBER INITIALIZER LIST: Meant for const members

    }
    void call() const {
        printf("My name is:   %s\n", this->name);
    }

    const char* name;   // The const member being referred to
};

int main() {
    Surname my_name{ "Tovalds" };
    my_name.call();
    return 0;
}
