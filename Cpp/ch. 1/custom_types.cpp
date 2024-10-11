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

// PODs (Plain Old Dataclasses)
// Essentially STRUCTS
struct Book {
    char name[256];
    char author[64];
    int year;
    int pages;
    bool hardcover;
};

union Variant {
    char string[0];
    int integer;
    double floating_point;
};

// CLASS
struct Clock {
    // Condtructor
    Clock(int year_in) {
        // Override with default if setter
        // returned a false, for a bad value
        if(!set_year(year_in))
            year = 2024;
    }
    // method
    void add_year() {
        year++;
    }
    // SETTER
    bool set_year(int new_year) {
        if (new_year < 2024)
            return false;
        year = new_year;
        return true;
    }
    // GETTER
    int get_year() {
        return year;
    }
    // ACCESS CONTROLS
    // Restrict arbitraty access from without class
    private:
        int year;   // accessible to method as class member
};

int main()
{
    // Initiallizing enum variables
    Snacks snack = Snacks::DOUGHNUT;
    Drinks black_label = WHISKY;

    switch (snack) {
        case Snacks::CANDY: {
            puts("Here's your candy");
            break;
        }
        case Snacks::DOUGHNUT: {
            puts("Here's your doughnut");
            break;
        }
        default: {
            puts("Snack may not be available");
        }
    }

    // DESIGNATED INITIALIZER
    Book my_book = {.name="Things Fall Apart", .author="Chinua Achebe", .year=1958};
    printf("My chosen book is: %s by %s \n", my_book.name, my_book.author);

    Variant v;
    v.floating_point = 2.1782818284;        // Dot Notation
    printf("Euler's number e: %f\n", v.floating_point);

    v.integer = 42;         // Dot Notation
    printf("The most common random seed is : %d\n", v.integer);

    Clock clock { 2024 };
    clock.set_year(2019);
    clock.add_year();
    printf("Next year:  %d\n", clock.get_year());

    return 0;
}
