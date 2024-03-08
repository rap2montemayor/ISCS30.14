#include "Logger.hpp"

const std::string levels[3] = {
    "[INFO]", "[WARNING]", "[ERROR]"
};

void Logger::log(const std::string& str, Level level) {
    static time_t now;
    static std::string buffer(128, 0);

    time(&now);
    buffer.assign(ctime(&now));
    buffer.pop_back();
    std::cout << levels[level] << '[' << buffer << "] " << str << std::endl;
}

void Logger::logInfo(const std::string& str) { log(str, Info); }
void Logger::logWarning(const std::string& str) { log(str, Warning); }
void Logger::logError(const std::string& str) { log(str, Error); }
