//
// Created by admin on 16/10/2023.
//

#include "Actor.h"


Actor::Actor(Graphics *renderer, Image *image, int x, int y) {
    Renderer = renderer;
    Sprite = image;
    X = x;
    Y = y;
}
