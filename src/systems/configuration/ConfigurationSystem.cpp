// ConfigurationSystem.cpp

#include <sys/stat.h>
#include <fstream>
#include <vector>
#include "SDL.h"
#include "systems/configuration/ConfigurationSystem.h"
#include "Engine.h"
#include "SDL_image.h"

ConfigurationSystem* ConfigurationSystem::_instance = nullptr;

ConfigurationSystem::ConfigurationSystem() {
    CreateDirectory();
    if (!IsFileExists(_windowDataFileName)) SetWindowData(_defaultWindowData);
}

ConfigurationSystem& ConfigurationSystem::GetInstance() {
    if (!_instance) {
        _instance = new ConfigurationSystem();
    }
    return *_instance;
}

WindowData* ConfigurationSystem::GetWindowData() {
    pugi::xml_document windowXml = GetConfigurationXml(_windowDataFileName);

    pugi::xml_node rootNode = windowXml.child("config");
    pugi::xml_node metaNode = rootNode.child("meta");
    pugi::xml_node windowNode = rootNode.child("window");

    if (!rootNode || !metaNode || !windowNode) {
        SDL_Log("Invalid XML Config File");
        return nullptr;
    }

    std::string windowName = metaNode.attribute("name").as_string();
    int windowWidth = windowNode.attribute("width").as_int();
    int windowHeight = windowNode.attribute("height").as_int();
    bool windowFullScreen = windowNode.attribute("fullscreen").as_bool();

    return new WindowData(windowName, windowWidth, windowHeight, windowFullScreen);
}

void ConfigurationSystem::SetWindowData(const WindowData& windowData) {
    pugi::xml_document windowXml;

    pugi::xml_node rootNode = windowXml.append_child("config");

    pugi::xml_node metaNode = rootNode.append_child("meta");
    metaNode.append_attribute("name").set_value(windowData.Name.c_str());

    pugi::xml_node windowNode = rootNode.append_child("window");
    windowNode.append_attribute("width").set_value(windowData.Width);
    windowNode.append_attribute("height").set_value(windowData.Height);
    windowNode.append_attribute("fullscreen").set_value(windowData.IsFullScreen);

    const auto path = GetSavePath(_windowDataFileName);
    windowXml.save_file(path.c_str());
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
        CharacterSpriteData& currentSpriteData = *sprites[characterId];

        currentSpriteData.XScale = characterNode.attribute("xScale").as_float();
        currentSpriteData.YScale = characterNode.attribute("yScale").as_float();

        pugi::xml_node stateNode = characterNode.child("state");

        while (stateNode) {
            State stateId = static_cast<State>(stateNode.attribute("id").as_int());

            currentSpriteData.States[stateId] = new StateTextureData();
            StateTextureData& currentStateTextureData = *currentSpriteData.States[stateId];

            currentStateTextureData.AnimSheetRows = stateNode.attribute("animSheetRows").as_int();
            currentStateTextureData.AnimSheetCols = stateNode.attribute("animSheetCols").as_int();
            currentStateTextureData.FirstSpriteRow = stateNode.attribute("firstSpriteRow").as_int();
            currentStateTextureData.FirstSpriteCol = stateNode.attribute("firstSpriteCol").as_int();
            currentStateTextureData.FrameCount = stateNode.attribute("frameCount").as_int();
            currentStateTextureData.AnimSpeed = stateNode.attribute("animSpeed").as_int();
            currentStateTextureData.Repeat = stateNode.attribute("repeat").as_bool();
            currentStateTextureData.Flip = static_cast<SDL_RendererFlip>(stateNode.attribute("flip").as_int());

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

                currentStateTextureData.Directions[directionId] = texture;

                directionNode = directionNode.next_sibling("direction");
            }

            stateNode = stateNode.next_sibling("state");
        }

        characterNode = characterNode.next_sibling("character");
    }

    return sprites;
}

pugi::xml_document ConfigurationSystem::GetConfigurationXml(const std::string& fileName) const {
    pugi::xml_document document;
    std::string documentPath = GetSavePath(fileName);
    pugi::xml_parse_result result = document.load_file(documentPath.c_str());

    SDL_Log("Document: %s Parse result: %s", documentPath.c_str(), result.description());

    return document;
}

void ConfigurationSystem::CreateDirectory() const {
    if (!IsDirectoryExists()) {
        int statResult = mkdir(_directory.c_str());
        if (!statResult) {
            SDL_Log("Folder Created: %s", _directory.c_str());
        } else {
            SDL_Log("Impossible to create folder");
        }
    }
}

bool ConfigurationSystem::IsDirectoryExists() const {
    struct stat buffer {};
    return stat(_directory.c_str(), &buffer) == 0;
}

bool ConfigurationSystem::IsFileExists(const std::string& fileName) const {
    struct stat buffer {};
    return stat(GetSavePath(fileName).c_str(), &buffer) == 0;
}

std::string ConfigurationSystem::GetSavePath(const std::string& filename) const {
    return _directory + filename;
}
