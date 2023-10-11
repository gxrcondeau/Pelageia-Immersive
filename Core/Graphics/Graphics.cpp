#include <cstdio>
#include "Graphics.h"

Graphics::Graphics(const char* windowName, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL Init failed: %s\n", SDL_GetError());
    }

    Window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (!Window) {
        fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
        SDL_Quit();
    }

    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!Renderer) {
        fprintf(stderr, "Renderer could not be created: %s\n", SDL_GetError());
        SDL_DestroyWindow(Window); // Clean up the window before quitting
        SDL_Quit();
    }
}

Image* Graphics::NewImage(const char* file) {
    Image* image = new Image();

    // TODO SDL_Image need to be installed

    //image->texture = IMG_LoadTexture(Renderer, file);

//    if (!image->texture) {
//        fprintf(stderr, "Failed to load image: %s\n", IMG_GetError());
//        delete image; // Clean up the image if loading failed
//        return nullptr;
//    }

    // Get the width and height from the source image
    SDL_QueryTexture(image->texture, NULL, NULL, &image->width, &image->height);

    return image;
}

Image* Graphics::NewImage(const char* file, int r, int g, int b) {
    Image* image = NewImage(file);

    // Set color key for transparency
    SDL_SetTextureColorMod(image->texture, r, g, b);

    return image;
}

bool Graphics::DrawImage(Image* img, int x, int y) {
    if (!Renderer || !img->texture)
        return false;

    SDL_Rect destinationRect;
    destinationRect.x = x;
    destinationRect.y = y;

    SDL_QueryTexture(img->texture, nullptr, nullptr, &destinationRect.w, &destinationRect.h);

    SDL_RenderCopy(Renderer, img->texture, nullptr, &destinationRect);

    return true;
}

bool Graphics::DrawImage(Image* img, int x, int y, int startX, int startY, int endX, int endY) {
    if (!Renderer || !img->texture)
        return false;

    SDL_Rect destinationRect;
    destinationRect.x = x;
    destinationRect.y = y;
    destinationRect.w = endX - startX;
    destinationRect.h = endY - startY;

    SDL_Rect sourceRect;
    sourceRect.x = startX;
    sourceRect.y = startY;
    sourceRect.w = destinationRect.w;
    sourceRect.h = destinationRect.h;

    SDL_RenderCopy(Renderer, img->texture, &sourceRect, &destinationRect);

    return true;
}

void Graphics::RenderFrame() {
    SDL_RenderPresent(Renderer);
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
    SDL_RenderClear(Renderer);
}
