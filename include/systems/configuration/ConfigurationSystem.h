//
// Created by pylinskyi.k on 14.12.2023.
//

#ifndef PELAGEIA_IMMERSIVE_CONFIGURATIONSYSTEM_H
#define PELAGEIA_IMMERSIVE_CONFIGURATIONSYSTEM_H

#include <string>
#include <memory>
#include "utilities/CoreTypeStructs.h"
#include "pugixml.hpp"

class ConfigurationSystem {
public:
    static ConfigurationSystem& GetInstance() {
        if (!_instance) {
            _instance = std::make_unique<ConfigurationSystem>();
        }
        return *_instance;
    }

    bool GetWindowData(std::unique_ptr<WindowData>& window);
    bool GetStaticTextureData(std::map<std::string, std::unique_ptr<StaticTextureData>>& textures);
    bool GetCharacterSpriteData(std::map<std::string, std::unique_ptr<CharacterSpriteData>>& sprites);

    ConfigurationSystem() {
        if (_instance) throw std::logic_error("ConfigurationSystem Instance already exists");
    }

protected:
    static std::unique_ptr<ConfigurationSystem> _instance;

    const std::string _directory = "./Config";
    const std::string _windowDataFileName = "window.xml";
    const std::string _staticTextureDataFileName = "staticTexture.xml";
    const std::string _characterSpriteDataFileName = "characterSprite.xml";

    void CreateConfiguration(const std::string& configName, const std::string& configXml) const;
    pugi::xml_document GetConfigurationXml(const std::string& fileName) const;

    bool IsDirectoryExists() const;
    bool IsFileExists(const std::string& fileName) const;
};

#endif  // PELAGEIA_IMMERSIVE_CONFIGURATIONSYSTEM_H
