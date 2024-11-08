#include <cstdio>
#include <sys/time.h>
#include <ctime>
#include <utility>

struct TimerClass {
    TimerClass(const char* name) {
        this->name = name;
        if (!gettimeofday(&this->now, &this->tz)) {
            this->timestamp = std::ctime(&now.tv_sec);
            printf("The time now is %s\n", this->timestamp);
        } else
            puts("Unable to get time of day");
    }

    TimerClass(const TimerClass& other) = default;
    TimerClass& operator=(const TimerClass& other) = default;

    TimerClass(TimerClass&& other) = default;
    TimerClass& operator=(TimerClass&& other) = default;

    ~TimerClass() {
        timeval later;
        if (!gettimeofday(&later, nullptr)) {
            char* timestamp_later = std::ctime(&later.tv_sec);
            printf("The time later is %s\n", timestamp_later);

            auto lifetime = (long)this->timestamp - (long)timestamp_later;
            printf("The object was alive for %ld seconds\n", lifetime);
        }
        printf("Destroying timer:  %s\n", this->name);
    }

    private:
        const char* name;
        char* timestamp;
        timeval now;
        timeval tz;
};

int main() {
    TimerClass tc { "Counter 1"};
    // TimerClass tc2 { tc };  // Copy construction
    // TimerClass tc3 { "Counter 3"};
    // tc3 = tc;   // Copy asignment

    // TimerClass tc4 { std::move(tc) };   // Move construction
    TimerClass tc5 { "Counter 5"};
    tc5 = std::move(tc);    // MOve assignment
    return 0;
}
