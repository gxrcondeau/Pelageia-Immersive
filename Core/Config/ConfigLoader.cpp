//
// Created by gxrcondeau on 2023-10-08.
//


#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "../Utils/Parser.h"
#include "ConfigLoader.h"


ConfigLoader::ConfigLoader() {
    createDefault();

    WindowParams params = getWindowParams();
    printf("Config: window name: %s, height: %i, width: %i, fullScreen: %i\n", params.name, params.height, params.width, params.fullScreen);
}

ConfigLoader::~ConfigLoader() {
}

pugi::xml_document ConfigLoader::getXml() const{
    if(!isConfigExist()) {
        createDefault();
    }

    pugi::xml_document doc;

    const char* const configPath = getConfigFullPath();
    pugi::xml_parse_result result = doc.load_file(configPath);

    delete[] configPath;
    std::cout << "Load result: " << result.description() << std::endl;
    return doc;
}

void ConfigLoader::createDefault() const{
    if(!isDirectoryExist()){
        mkdir(configDirectory);
    }

    if(!isConfigExist()) {
        createFile();
    }
}

void ConfigLoader::createFile() const{

    const char* const outFilePath = getConfigFullPath();

    std::ofstream outfile (outFilePath);
    outfile << configDefaultString;

    delete[] outFilePath;
    outfile.close();
}

char* ConfigLoader::getConfigFullPath() const {
    size_t fullPathLength = strlen(configDirectory) + strlen("/") + strlen(configFileName) + 1;

    char* fullPath = new char[fullPathLength];

    strcpy(fullPath, configDirectory);

    strcat(fullPath, "/");
    strcat(fullPath, configFileName);

    return fullPath;
}

bool ConfigLoader::isConfigExist() const {
    struct stat buffer{};
    return stat(getConfigFullPath(), &buffer) == 1;
}

bool ConfigLoader::isDirectoryExist() const {
    struct stat buffer{};
    return stat(configDirectory, &buffer) == 1;
}

void ConfigLoader::update() {
}

WindowParams ConfigLoader::getWindowParams() const{
    const auto config = getXml();

    const auto name = config.child("PeImConfig").child("meta").attribute("name").value();
    const auto width = config.child("PeImConfig").child("window").attribute("width").value();
    const auto height = config.child("PeImConfig").child("window").attribute("height").value();
    const auto fullscreen = config.child("PeImConfig").child("window").attribute("fullscreen").value();

    return WindowParams{
            name,
            Parser::TryParseInt(width).first,
            Parser::TryParseInt(height).first,
            Parser::TryParseBool(fullscreen)
    };
}