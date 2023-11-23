//
// Created by gxrcondeau on 2023-10-08.
//

#include <sys/stat.h>
#include <io.h>
#include <fstream>
#include <vector>
#include "Utils/Config/ConfigLoader.h"
#include "SDL.h"

ConfigLoader* ConfigLoader::s_Instance = nullptr;

ConfigLoader::ConfigLoader()
{
    CreateConfig(WindowParamsFileName, WindowParamsDefaultXml);
}

WindowParams* ConfigLoader::GetWindowParams()
{
    if (m_WindowParams) return m_WindowParams;

    pugi::xml_document windowXml = GetConfigXml(WindowParamsFileName);

    pugi::xml_node rootNode = windowXml.child("config");
    pugi::xml_node metaNode = rootNode.child("meta");
    pugi::xml_node windowNode = rootNode.child("window");

    if (!rootNode || !metaNode || !windowNode)
    {
        SDL_Log("Invalid XML Config File");
        return nullptr;
    }

    std::string windowName = metaNode.attribute("name").as_string();
    int windowWidth = windowNode.attribute("width").as_int();
    int windowHeight = windowNode.attribute("height").as_int();
    int windowFullScreen = windowNode.attribute("fullscreen").as_int();

    return m_WindowParams = new WindowParams(windowName, windowWidth, windowHeight, windowFullScreen);
}

pugi::xml_document ConfigLoader::GetConfigXml(std::string configName) const
{
    pugi::xml_document document;
    std::string documentPath = ConfigDirectory + configName;
    pugi::xml_parse_result result = document.load_file(documentPath.c_str());

    SDL_Log("Document: %s Parse result: %s", documentPath.c_str(), result.description());

    return document;
}

void ConfigLoader::CreateConfig(std::string configName, std::string configXml) const
{
    if (!IsDirectoryExist())
    {
        int stat = mkdir(ConfigDirectory.c_str());
        if (!stat)
            SDL_Log("Folder Created: %s", ConfigDirectory.c_str());
        else
            SDL_Log("Impossible create folder");
    }

    if (!IsFileExist(configName))
    {
        std::string filePath = ConfigDirectory + configName;
        std::ofstream outfile(filePath);
        outfile << configXml;

        outfile.close();
    }
}

bool ConfigLoader::IsDirectoryExist() const
{
    struct stat buffer {};
    return stat(ConfigDirectory.c_str(), &buffer) == 0;
}

bool ConfigLoader::IsFileExist(std::string configName) const
{
    struct stat buffer {};
    std::string documentPath = ConfigDirectory + configName;
    return stat(documentPath.c_str(), &buffer) == 0;
}