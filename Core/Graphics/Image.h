//
// Created by pylinskyi.k on 11.10.2023.
//

#ifndef PELAGEIA_IMMERSIVE_IMAGE_H
#define PELAGEIA_IMMERSIVE_IMAGE_H


#include <SDL.h>

class Image {
private:
    SDL_Texture* texture;
    int width;
    int height;
public:
    friend class Graphics;

    int GetWidth();
    int GetHeight();
};


#endif //PELAGEIA_IMMERSIVE_IMAGE_H
