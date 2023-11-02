//
// Created by admin on 19/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_TEXTUREMANAGER_H
#define PELAGEIA_IMMERSIVE_TEXTUREMANAGER_H

#include "SDL.h"
#include <string>
#include <map>


class TextureManager {
public:
    static TextureManager* GetInstance(){
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager();
    }

    bool Load(std::string id, std::string filename);
    void Drop(std::string id);
    void Clean();

    void Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
    TextureManager() {};
    std::map<std::string, SDL_Texture*> m_TextureMap;
    static TextureManager* s_Instance;
};


#endif //PELAGEIA_IMMERSIVE_TEXTUREMANAGER_H
