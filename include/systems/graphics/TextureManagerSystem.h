//
// Created by pylinskyi.k on 13.12.2023.
//

#ifndef PELAGEIA_IMMERSIVE_TEXTUREMANAGERSYSTEM_H
#define PELAGEIA_IMMERSIVE_TEXTUREMANAGERSYSTEM_H

#include <string>
#include <stdexcept>
#include "systems/configuration/ConfigurationSystem.h"
#include "utilities/CoreTypeStructs.h"

class TextureManagerSystem {
public:
    static TextureManagerSystem& GetInstance() {
        if (!_instance) _instance = new TextureManagerSystem();
        return *_instance;
    };

    bool LoadTexture(std::string id, std::string source, SDL_RendererFlip flip);
    bool LoadTextures() { return ConfigurationSystem::GetInstance().GetStaticTextureData(_textureMap); }
    bool LoadCharacterTextures() { return ConfigurationSystem::GetInstance().GetCharacterSpriteData(_spriteMap); }

    void Draw(std::string id, int x, int y);
    void DrawTile(std::string id, int tileSize, int row, int col, int x, int y);
    void DrawFrame(std::string id, State state, Direction direction, int frame, int x, int y);

    void DropTexture(std::string id);
    void ClearTextureMap();

protected:
    TextureManagerSystem() { if (_instance) throw std::logic_error("TextureManagerSystem Instance already exists"); };
    virtual ~TextureManagerSystem() { };

    static TextureManagerSystem* _instance;

    std::map<std::string, std::unique_ptr<StaticTextureData>> _textureMap;
    std::map<std::string, std::unique_ptr<CharacterSpriteData>> _spriteMap;
};

#endif  // PELAGEIA_IMMERSIVE_TEXTUREMANAGERSYSTEM_H
