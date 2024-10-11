#include <cstdio>

// Scoped enum
enum class Snacks {
    CANDY, DOUGHNUT
};

// Unscoped enum
// Less safe; AVOID
// For backwards compatibility with C
enum Drinks {
    MARGARITA, TEQUILA, WHISKY
};

int main()
{
    // Initiallizing enum variables
    Snacks bagel = Snacks::DOUGHNUT;
    Drinks black_label = WHISKY;

    return 0;
}
