//
// Created by admin on 09/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_PEIMLOGGER_H
#define PELAGEIA_IMMERSIVE_PEIMLOGGER_H


#include <string>
#include <map>
#include "SDL_log.h"

class PeImLogger {
public:
    void static LogToFile(void* userdata, int category, SDL_LogPriority priority, const char* message);
};


#endif //PELAGEIA_IMMERSIVE_PEIMLOGGER_H
