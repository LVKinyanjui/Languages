#include <cstdio>

struct Logger {
    virtual ~Logger() = default;
    virtual void log_transfer(long from, long to, double amount) = 0;
};

struct AccountDatabase {
    virtual ~AccountDatabase() = default;
    virtual void set_get_amounts(long id) = 0;
};

struct InMemoryAccountDatabase: AccountDatabase {
    void set_get_amounts(long id) {
        printf("Your balance: ");
    }
};

struct FileLogger: Logger {
    void log_transfer(long from, long to, double amount) override {

        printf("[file] %ld -> %ld: %f\n", from, to, amount);
    }
};

struct ConsoleLogger: Logger {
    ConsoleLogger(const char* input) {this->input = input;}
    void log_transfer(long from, long to, double amount) override {
        printf("%s \n%ld -> %ld: %f\n", input, from, to, amount);
    }
    const char* input;
};

struct Bank {
    Bank(Logger & logger, AccountDatabase& database)
    : logger{ logger }, database{ database } {}

    void make_transfer(long from, long to, double amount) {
        logger.log_transfer(from, to, amount);
    }

    private:
        Logger& logger;
        AccountDatabase& database;
};

int main() {
    ConsoleLogger logger { "Console Logger" };
    InMemoryAccountDatabase database;
    Bank bank{ logger, database }; // constructor injection. fixed at object construction
    bank.make_transfer(1000, 2000, 49.95);
    return 0;
}
