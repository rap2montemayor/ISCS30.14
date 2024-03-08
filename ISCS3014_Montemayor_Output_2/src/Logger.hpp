#pragma once

#include <ctime>
#include <iostream>
#include <string>

// There are really just print functions with timestamps
// These were written very hastily.

namespace Logger {

enum Level { Info, Warning, Error };
void log(const std::string& str, Level level);
void logInfo(const std::string& str);
void logWarning(const std::string& str);
void logError(const std::string& str);

}