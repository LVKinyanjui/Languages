#include <cstdio>

struct Tracer {
    Tracer(const char* name): name{ name } {
        printf("%s constructed,\n", name);
    }
    ~Tracer() {
        printf("%s destructed,\n", name);
    }
    private:
        const char* const name;
};

static Tracer t1{ "Static Variable" };
thread_local Tracer t2{ "Thread-Local Variable" };

int main() {
    Tracer t3 { "Automatic Variable" };
    const auto* t4 { "Dynamic Variable" };
    return 0;
}
