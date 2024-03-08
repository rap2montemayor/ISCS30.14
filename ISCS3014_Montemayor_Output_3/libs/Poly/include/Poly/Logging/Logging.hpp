#pragma once

#include <iostream>
#include <iomanip>
#include <chrono>

namespace poly {

enum Level { Info, Warning, Error };

template <typename ...Args>
static void log(Level level, Args&&... args);

template <typename ...Args>
static void logInfo(Args&&... args);

template <typename ...Args>
static void logWarning(Args&&... args);

template <typename ...Args>
static void logError(Args&&... args);

}

#include "Logging.inl"