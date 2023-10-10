//
// Created by gxrcondeau on 2023-10-08.
//

#ifndef PELAGEIA_IMMERSIVE_CONFIGLOADER_H
#define PELAGEIA_IMMERSIVE_CONFIGLOADER_H

#include "../Include/pugixml.hpp"

class ConfigLoader {
public:
    pugi::xml_parse_result getXml() const;

    // TODO: add config update method
    void update();

    void createDefault() const;

protected:
    const char* const configDirectory = "./Config";
    const char* const configFileName = "Engine.xml";

    char* getConfigFullPath() const;

    void createFile() const;

    bool isConfigExist() const;
    bool isDirectoryExist() const;
    bool isLoaded;

private:
    const char* const configDefaultString = "<?xml version=\"1.0\"?>\n"
                                            "<PEIM>\n"
                                            "    <build version=\"0.1\" channel=\"dev\"/>\n"
                                            "    <window width=\"1280\" height=\"720\" fullscreen=\"0\"/>\n"
                                            "</PEIM>";
};


#endif //PELAGEIA_IMMERSIVE_CONFIGLOADER_H
