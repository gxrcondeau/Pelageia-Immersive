//
// Created by admin on 09/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_PEIMLOGGER_H
#define PELAGEIA_IMMERSIVE_PEIMLOGGER_H


#include <string>
#include <map>
#include "SDL_log.h"


enum PeImLogCategory{
    SYSTEM,
    CONFIG,
    GRAPHICS,
    INPUT
};

class PeImLogger {
public:
    void static Info(const char* message, ...);
};


#endif //PELAGEIA_IMMERSIVE_PEIMLOGGER_H
