//
// Created by admin on 09/10/2023.
//

#include "SDL.h"
#include <cstdio>
#include <chrono>
#include <ctime>
#include <cstdarg>
#include "PeImLogger.h"




void PeImLogger::Info(const char *message, ...) {
    const auto timeNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    // Create a va_list for variable arguments
    va_list args;
    va_start(args, message);

    // Use vprintf to handle the formatted output
    printf("%s [Info] ", ctime(&timeNow));
    vprintf(message, args);
    printf("\n");

    // End the va_list
    va_end(args);
}

