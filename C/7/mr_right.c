#include <stdio.h>
#include <string.h>

int NUM_ADS = 7;

char *ADS[] = {
    "William: SBM GSOH likes sports, TV, dining",
    "Matt: SWM NS likes art, movies, theater",
    "Luis: SLM ND likes books, theater, art",
    "Mike: DWM DS likes trucks, sports and bieber",
    "Peter: SAM likes chess, working out and art",
    "Josh: SJM likes sports, movies and theater",
    "Jed: DBM likes theater, books and dining"
};

int sports_no_bieber(char *s) {
    return strstr(s, "sports") && !strstr(s, "bieber");
}

int sports_or_workout(char *s) {
    return strstr(s, "sports") || strstr(s, "working out");
}

int arts_theater_or_dining(char *s) {
    return strstr(s, "arts") || strstr(s, "theater") || strstr(s, "dining");
}

void find(int (*match)(char*))
{
    int i;
    puts("Search results:");
    puts(" ... \n");

    for(i=0; i<NUM_ADS; i++) {
        if (match(ADS[i]))
                printf("%s\n", ADS[i]);
    }
    puts("Mr Right Found");
}

int main() 
{
    // Creating pointers to funcions
    int (*sports_no_bieber_fn) (char*);
    sports_no_bieber_fn = sports_no_bieber;

    int (*sports_or_workout_fn) (char*);
    sports_or_workout_fn = sports_or_workout;

    int (*arts_theater_or_dining_fn) (char *);
    arts_theater_or_dining_fn = arts_theater_or_dining;

    find(sports_no_bieber_fn);
    find(sports_or_workout_fn);
    find(arts_theater_or_dining_fn);

    return 0;
}