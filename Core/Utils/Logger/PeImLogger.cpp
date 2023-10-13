//
// Created by admin on 09/10/2023.
//

#include "SDL.h"
#include <cstdio>
#include <chrono>
#include <ctime>
#include "PeImLogger.h"


void PeImLogger::Info(const char *message, ...) {
    const auto timeNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    printf("(%s) [Info] %s\n", ctime(&timeNow), message);
}
