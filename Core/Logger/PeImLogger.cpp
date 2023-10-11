//
// Created by admin on 09/10/2023.
//

#include "SDL.h"
#include <cstdio>
#include "PeImLogger.h"

void PeImLogger::LogToFile(void *userdata, int category, SDL_LogPriority priority, const char *message) {
    SDL_LogMessage(category, priority, "%s", message);

    FILE* file = fopen("C:\\PeImLogs\\logfile.log", "a");
    if (file) {
        fprintf(file, "[%i] %s\n", category, message);
        fclose(file);
    }
}
