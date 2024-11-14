#include <cstdio>

struct Logger {
    virtual ~Logger() = default;
    virtual void log_transfer(long from, long to, double amount) = 0;
};

struct FileLogger: Logger {
    void log_transfer(long from, long to, double amount) override {

        printf("[file] %ld -> %ld: %f\n", from, to, amount);
    }
};

struct ConsoleLogger: Logger {
    void log_transfer(long from, long to, double amount) override {
        printf("%ld -> %ld: %f\n", from, to, amount);
    }
};

struct Bank {
    Bank(Logger & logger) : logger{ logger } {}

    void make_transfer(long from, long to, double amount) {
        logger.log_transfer(from, to, amount);
    }

    private:
        Logger& logger;
};

int main() {
    ConsoleLogger logger;
    Bank bank{ logger }; // constructor injection. fixed at object construction
    bank.make_transfer(1000, 2000, 49.95);
    return 0;
}
