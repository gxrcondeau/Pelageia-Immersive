//
// Created by gxrcondeau on 2023-10-08.
//

#include <sys/stat.h>
#include <io.h>
#include <fstream>
#include <vector>
#include "Utils/Config/ConfigLoader.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Engine.h"

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
    bool windowFullScreen = windowNode.attribute("fullscreen").as_bool();
    bool windowIsometric = metaNode.attribute("isometric").as_bool();

    return windowConfig = new WindowConfig(windowName, windowWidth, windowHeight, windowFullScreen, windowIsometric);
}

std::map<std::string, CharacterTexturesConfig*> ConfigLoader::GetCharactersTexturesConfig()
{
    std::map<std::string, CharacterTexturesConfig*> config;

    pugi::xml_document characterTextureXml = GetConfigXml(CharacterTextureParamsFileName);

    pugi::xml_node rootNode = characterTextureXml.child("config");
    pugi::xml_node characterNode = rootNode.child("character");

    while (characterNode)
    {
        std::string characterId = characterNode.attribute("id").as_string();
        config[characterId] = new CharacterTexturesConfig();
        config[characterId]->XScale = characterNode.attribute("xScale").as_float();
        config[characterId]->YScale = characterNode.attribute("yScale").as_float();

        pugi::xml_node stateNode = characterNode.child("state");

        while (stateNode)
        {
            CharacterState stateId = static_cast<CharacterState>(stateNode.attribute("id").as_int());

            config[characterId]->StateMap[stateId] = new CharaterStateConfig();
            config[characterId]->StateMap[stateId]->AnimSheetRows = stateNode.attribute("animSheetRows").as_int();
            config[characterId]->StateMap[stateId]->AnimSheetCols = stateNode.attribute("animSheetCols").as_int();
            config[characterId]->StateMap[stateId]->FirstSpriteRow = stateNode.attribute("firstSpriteRow").as_int();
            config[characterId]->StateMap[stateId]->FirstSpriteCol = stateNode.attribute("firstSpriteCol").as_int();
            config[characterId]->StateMap[stateId]->FrameCount = stateNode.attribute("frameCount").as_int();
            config[characterId]->StateMap[stateId]->AnimSpeed = stateNode.attribute("animSpeed").as_int();
            config[characterId]->StateMap[stateId]->Repeat = stateNode.attribute("repeat").as_bool();
            config[characterId]->StateMap[stateId]->Flip = static_cast<SDL_RendererFlip>(stateNode.attribute("flip").as_int());

            pugi::xml_node directionNode = stateNode.child("direction");

            while (directionNode)
            {
                CharacterDirection directionId = static_cast<CharacterDirection>(directionNode.attribute("id").as_int());

                std::string filePath = directionNode.attribute("filePath").as_string();

                SDL_Surface* surface = IMG_Load(filePath.c_str());
                if (!surface)
                {
                    SDL_Log("Failed to load texture: %s %s", filePath.c_str(), SDL_GetError());
                    throw std::runtime_error("Failed to load texture");
                }

                SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
                if (!texture)
                {
                    SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
                    throw std::runtime_error("Failed to create texture from surface");
                }

                config[characterId]->StateMap[stateId]->DirectionMap[directionId] = texture;

                directionNode = directionNode.next_sibling("direction");
            }

            stateNode = stateNode.next_sibling("state");
        }

        characterNode = characterNode.next_sibling("character");
    }

    return config;
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