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
    CreateConfig(WindowParamsFileName, windowParamsDefaultXml);
    CreateConfig(CharacterTextureParamsFileName, charactersTexturesParamsXml);
}

WindowConfig* ConfigLoader::GetWindowConfig()
{
    if (windowConfig) return windowConfig;

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

    return windowConfig = new WindowConfig(windowName, windowWidth, windowHeight, windowFullScreen);
}

std::map<std::string, CharacterTexturesConfig*> ConfigLoader::GetCharactersTexturesConfig()
{
    pugi::xml_document characterTextureXml = GetConfigXml(CharacterTextureParamsFileName);

    pugi::xml_node rootNode = characterTextureXml.child("config");
    pugi::xml_node characterNode = rootNode.child("character");

    while (characterNode)
    {
        std::string characterId = characterNode.attribute("id").as_string();
        charactersTexturesConfig[characterId] = new CharacterTexturesConfig();

        pugi::xml_node stateNode = characterNode.child("state");

        while (stateNode)
        {
            charactersTexturesConfig[characterId]->AnimSheetRows = stateNode.attribute("animSheetRows").as_int();
            charactersTexturesConfig[characterId]->AnimSheetCols = stateNode.attribute("animSheetCols").as_int();
            charactersTexturesConfig[characterId]->StartSpriteRow = stateNode.attribute("startSpriteRow").as_int();
            charactersTexturesConfig[characterId]->FrameCount = stateNode.attribute("frameCount").as_int();
            charactersTexturesConfig[characterId]->AnimSpeed = stateNode.attribute("animSpeed").as_int();
            charactersTexturesConfig[characterId]->Flip = static_cast<SDL_RendererFlip>(stateNode.attribute("flip").as_int());

            CharacterState stateId = static_cast<CharacterState>(stateNode.attribute("id").as_int());

            pugi::xml_node directionNode = stateNode.child("direction");

            while (directionNode)
            {
                CharacterDirection directionId = static_cast<CharacterDirection>(directionNode.attribute("id").as_int());
                charactersTexturesConfig[characterId]->TextureMap[stateId][directionId] = directionNode.attribute("filePath").as_string();

                directionNode = directionNode.next_sibling("direction");
            }

            stateNode = stateNode.next_sibling("state");
        }

        characterNode = characterNode.next_sibling("character");
    }

    return charactersTexturesConfig;
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
    struct stat buffer
    {
    };
    return stat(ConfigDirectory.c_str(), &buffer) == 0;
}

bool ConfigLoader::IsFileExist(std::string configName) const
{
    struct stat buffer
    {
    };
    std::string documentPath = ConfigDirectory + configName;
    return stat(documentPath.c_str(), &buffer) == 0;
}