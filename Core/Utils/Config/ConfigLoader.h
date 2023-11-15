//
// Created by gxrcondeau on 2023-10-08.
//

#ifndef PELAGEIA_IMMERSIVE_CONFIGLOADER_H
#define PELAGEIA_IMMERSIVE_CONFIGLOADER_H

#include "../../Include/Pugi/pugixml.hpp"

struct WindowParams{
    std::string Name;
    int Width;
    int Height;
    bool FullScreen;
};

class ConfigLoader {
public:
    static ConfigLoader* GetInstance() { return s_Instance = ( s_Instance != nullptr ? s_Instance : new ConfigLoader() ); }

    WindowParams* GetWindowParams() const;

    void CreateConfig(std::string configName, std::string configXml) const;

protected:
    const std::string ConfigDirectory = "./Config/";
    const std::string WindowParamsFileName = "WindowParams.xml";

    pugi::xml_document GetConfigXml(std::string configName) const;

    bool IsDirectoryExist() const;
    bool IsFileExist(std::string configName) const;
    bool IsLoaded;

private:
    ConfigLoader();
    static ConfigLoader* s_Instance;

    std::string WindowParamsDefaultXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                            "<config>\n"
                                            "    <build version=\"0.1\" channel=\"dev\"/>\n"
                                            "    <meta name=\"Pelageia Immersive\"/>\n"
                                            "    <window width=\"320\" height=\"320\" fullscreen=\"0\"/>\n"
                                            "</config>";
};


#endif //PELAGEIA_IMMERSIVE_CONFIGLOADER_H
