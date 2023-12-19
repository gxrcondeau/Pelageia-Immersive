// ConfigurationSystem.h

#ifndef PELAGEIA_IMMERSIVE_CONFIGURATIONSYSTEM_H
#define PELAGEIA_IMMERSIVE_CONFIGURATIONSYSTEM_H

#include <string>
#include <memory>
#include <map>
#include "utilities/CoreTypeStructs.h"
#include "pugixml.hpp"

class ConfigurationSystem {
public:
    static ConfigurationSystem& GetInstance();

    WindowData* GetWindowData();
    void SetWindowData(const WindowData& windowData);

    std::map<std::string, std::unique_ptr<StaticTextureData>> GetStaticTextureData();
    std::map<std::string, std::unique_ptr<CharacterSpriteData>> GetCharacterSpriteData();

private:
    ConfigurationSystem();

    static ConfigurationSystem* _instance;

    const std::string _directory = "Config/";
    const std::string _windowDataFileName = "window.xml";
    const std::string _staticTextureDataFileName = "staticTexture.xml";
    const std::string _characterSpriteDataFileName = "characterSprite.xml";

    void CreateDirectory() const;
    std::string GetSavePath(const std::string& filename) const;
    pugi::xml_document GetConfigurationXml(const std::string& fileName) const;
    bool IsDirectoryExists() const;
    bool IsFileExists(const std::string& fileName) const;

    const WindowData _defaultWindowData = { "Pelageia", 400, 300, false };
};

#endif  // PELAGEIA_IMMERSIVE_CONFIGURATIONSYSTEM_H
