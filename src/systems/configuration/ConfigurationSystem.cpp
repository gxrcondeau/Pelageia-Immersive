#include <sys/stat.h>
#include <fstream>
#include <vector>
#include "SDL.h"
#include "systems/configuration/ConfigurationSystem.h"
#include "Engine.h"
#include "SDL_image.h"

ConfigurationSystem* ConfigurationSystem::_instance = nullptr;

WindowData* ConfigurationSystem::GetWindowData() {
    pugi::xml_document windowXml = GetConfigurationXml(_windowDataFileName);

    pugi::xml_node rootNode = windowXml.child("config");
    pugi::xml_node metaNode = rootNode.child("meta");
    pugi::xml_node windowNode = rootNode.child("window");

    if (!rootNode || !metaNode || !windowNode) {
        SDL_Log("Invalid XML Config File");
    }

    std::string windowName = metaNode.attribute("name").as_string();
    int windowWidth = windowNode.attribute("width").as_int();
    int windowHeight = windowNode.attribute("height").as_int();
    bool windowFullScreen = windowNode.attribute("fullscreen").as_bool();
    bool windowIsometric = metaNode.attribute("isometric").as_bool();

    return new WindowData(windowName, windowWidth, windowHeight, windowFullScreen, windowIsometric);
}

std::map<std::string, std::unique_ptr<StaticTextureData>> ConfigurationSystem::GetStaticTextureData() {
    return std::map<std::string, std::unique_ptr<StaticTextureData>>();
}

std::map<std::string, std::unique_ptr<CharacterSpriteData>> ConfigurationSystem::GetCharacterSpriteData() {
    std::map<std::string, std::unique_ptr<CharacterSpriteData>> sprites;

    pugi::xml_document characterTextureXml = GetConfigurationXml(_characterSpriteDataFileName);

    pugi::xml_node rootNode = characterTextureXml.child("config");
    pugi::xml_node characterNode = rootNode.child("character");

    while (characterNode) {
        std::string characterId = characterNode.attribute("id").as_string();
        sprites[characterId] = std::make_unique<CharacterSpriteData>();
        sprites[characterId]->XScale = characterNode.attribute("xScale").as_float();
        sprites[characterId]->YScale = characterNode.attribute("yScale").as_float();

        pugi::xml_node stateNode = characterNode.child("state");

        while (stateNode) {
            State stateId = static_cast<State>(stateNode.attribute("id").as_int());

            sprites[characterId]->States[stateId] = new StateTextureData();
            sprites[characterId]->States[stateId]->AnimSheetRows = stateNode.attribute("animSheetRows").as_int();
            sprites[characterId]->States[stateId]->AnimSheetCols = stateNode.attribute("animSheetCols").as_int();
            sprites[characterId]->States[stateId]->FirstSpriteRow = stateNode.attribute("firstSpriteRow").as_int();
            sprites[characterId]->States[stateId]->FirstSpriteCol = stateNode.attribute("firstSpriteCol").as_int();
            sprites[characterId]->States[stateId]->FrameCount = stateNode.attribute("frameCount").as_int();
            sprites[characterId]->States[stateId]->AnimSpeed = stateNode.attribute("animSpeed").as_int();
            sprites[characterId]->States[stateId]->Repeat = stateNode.attribute("repeat").as_bool();
            sprites[characterId]->States[stateId]->Flip = static_cast<SDL_RendererFlip>(stateNode.attribute("flip").as_int());

            pugi::xml_node directionNode = stateNode.child("direction");

            while (directionNode) {
                Direction directionId = static_cast<Direction>(directionNode.attribute("id").as_int());

                std::string filePath = directionNode.attribute("filePath").as_string();

                SDL_Surface* surface = IMG_Load(filePath.c_str());
                if (!surface) {
                    SDL_Log("Failed to load texture: %s %s", filePath.c_str(), SDL_GetError());
                }

                SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance().GetRenderer(), surface);
                if (!texture) {
                    SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
                }

                sprites[characterId]->States[stateId]->Directions[directionId] = texture;

                directionNode = directionNode.next_sibling("direction");
            }

            stateNode = stateNode.next_sibling("state");
        }

        characterNode = characterNode.next_sibling("character");
    }

    return sprites;
}

void ConfigurationSystem::CreateConfiguration(const std::string& configName, const std::string& configXml) const {
    if (!IsDirectoryExists()) {
        int statResult = mkdir(_directory.c_str());
        if (statResult != 0) {
            SDL_Log("Failed to create folder: %s", _directory.c_str());
            throw std::runtime_error("Failed to create folder");
        } else {
            SDL_Log("Folder Created: %s", _directory.c_str());
        }
    }

    if (!IsFileExists(configName)) {
        std::string filePath = _directory + configName;
        std::ofstream outfile(filePath);
        outfile << configXml;

        outfile.close();
    }
}

pugi::xml_document ConfigurationSystem::GetConfigurationXml(const std::string& fileName) const {
    pugi::xml_document document;
    std::string documentPath = _directory + fileName;
    pugi::xml_parse_result result = document.load_file(documentPath.c_str());

    SDL_Log("Document: %s Parse result: %s", documentPath.c_str(), result.description());

    return document;
}

bool ConfigurationSystem::IsDirectoryExists() const {
    struct stat buffer {};
    return stat(_directory.c_str(), &buffer) == 0;
}

bool ConfigurationSystem::IsFileExists(const std::string& fileName) const {
    struct stat buffer {};
    std::string documentPath = _directory + fileName;
    return stat(documentPath.c_str(), &buffer) == 0;
}
