//
// Created by gxrcondeau on 2023-10-08.
//


#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "ConfigLoader.h"


pugi::xml_parse_result ConfigLoader::getXml() const{
    if(!isConfigExist()) {
        createDefault();
    }
    pugi::xml_document doc;

    const char* const configPath = getConfigFullPath();
    pugi::xml_parse_result result = doc.load_file(configPath);

    delete[] configPath;
    std::cout << "Load result: " << result.description() << ", engine version: " << doc.child("PEIM").child("build").attribute("version").value() << ":" << doc.child("PEIM").child("build").attribute("channel").value() << std::endl;

    return result;
}

void ConfigLoader::createDefault() const{
    if(isConfigExist()) return;

    if(!isDirectoryExist()){
        mkdir(configDirectory);
    }

    createFile();
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
