//
// Created by pylinskyi.k on 13.12.2023.
//

#ifndef PELAGEIA_IMMERSIVE_LAYERCOMPONENT_H
#define PELAGEIA_IMMERSIVE_LAYERCOMPONENT_H

#include "components/BaseComponent.h"

class LayerComponent : BaseComponent {
public:
    virtual void Render() = 0;

};

#endif  // PELAGEIA_IMMERSIVE_LAYERCOMPONENT_H