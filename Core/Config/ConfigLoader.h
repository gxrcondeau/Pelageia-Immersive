//
// Created by gxrcondeau on 2023-10-08.
//

#ifndef PELAGEIA_IMMERSIVE_CONFIGLOADER_H
#define PELAGEIA_IMMERSIVE_CONFIGLOADER_H

#include "../Include/Pugi/pugixml.hpp"

struct WindowParams{
    int xPos;
    int yPos;
    int width;
    int height;
    bool fullScreen;
};

class ConfigLoader {
public:
    ConfigLoader();
    ~ConfigLoader();

    pugi::xml_document getXml() const;

    WindowParams getWindowParams();

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
                                            "<PeImConfig>\n"
                                            "    <build version=\"0.1\" channel=\"dev\"/>\n"
                                            "    <window xpos=\"0\" ypos=\"0\" width=\"1280\" height=\"720\" fullscreen=\"0\"/>\n"
                                            "</PeImConfig>";
};


#endif //PELAGEIA_IMMERSIVE_CONFIGLOADER_H
