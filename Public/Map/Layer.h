//
// Created by pylinskyi.k on 03.11.2023.
//

#ifndef PELAGEIA_IMMERSIVE_LAYER_H
#define PELAGEIA_IMMERSIVE_LAYER_H

class Layer
{
public:
    virtual void Render() = 0;
    virtual void Update(int dt) = 0;
};

#endif  // PELAGEIA_IMMERSIVE_LAYER_H
