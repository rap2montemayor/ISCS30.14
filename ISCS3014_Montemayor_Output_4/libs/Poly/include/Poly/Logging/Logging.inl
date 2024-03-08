#include "Logging.hpp"

// To do: don't copy paste

namespace poly {

template <typename ...Args>
void log(Level level, Args&&... args) {
    switch (level) {
    case Level::Info:
        logInfo(args...);
        break;
    case Level::Warning:
        logWarning(args...);
        break;
    case Level::Error:
        logError(args...);
        break;
    }
}

template <typename ...Args>
void logInfo(Args&&... args) {
    std::cout << "[INFO]";
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::cout << "[" << std::put_time(&tm, "%c") << "] ";
    ((std::cout << args << ' '), ...);
    std::cout << std::endl;
}

template <typename ...Args>
void logWarning(Args&&... args) {
    std::cout << "[WARNING]";
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::cout << "[" << std::put_time(&tm, "%c") << "] ";
    ((std::cout << args << ' '), ...);
    std::cout << std::endl;
}

template <typename ...Args>
void logError(Args&&... args) {
    std::cout << "[ERROR]";
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::cout << "[" << std::put_time(&tm, "%c") << "] ";
    ((std::cout << args << ' '), ...);
    std::cout << std::endl;
}

}