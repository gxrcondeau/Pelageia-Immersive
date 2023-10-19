//
// Created by pylinskyi.k on 11.10.2023.
//

#ifndef PELAGEIA_IMMERSIVE_GRAPHICS_H
#define PELAGEIA_IMMERSIVE_GRAPHICS_H


#include <SDL.h>
#include "Image.h"

class Graphics {
private:
    SDL_Window* Window;
    SDL_Renderer* Renderer;

public:
    Graphics(const char* const windowName, int width, int height);

    Image* NewImage(const char* file);
    Image* NewImage(const char* file, int r, int g, int b);
    bool DrawImage(Image* img, int x, int y);
    bool DrawImage(Image* img, int x, int y, int startX, int startY, int endX, int endY);

    void RenderFrame();
};


#endif //PELAGEIA_IMMERSIVE_GRAPHICS_H
