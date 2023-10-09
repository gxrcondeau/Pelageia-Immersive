//
// Created by gxrcondeau on 2023-10-08.
//

#ifndef PELAGEIA_IMMERSIVE_CONFIGLOADER_H
#define PELAGEIA_IMMERSIVE_CONFIGLOADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include "../Include/pugixml.hpp"

class ConfigLoader {
public:
    ConfigLoader();

    ~ConfigLoader();

    void load();

    // TODO: add config update method
    void update();

    void reset();

    void configCheck();

private:
    bool configExist;
    bool isLoaded;
};


#endif //PELAGEIA_IMMERSIVE_CONFIGLOADER_H
