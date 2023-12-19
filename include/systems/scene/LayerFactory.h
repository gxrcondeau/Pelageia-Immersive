//
// Created by pylinskyi.k on 19.12.2023.
//

#ifndef PELAGEIA_IMMERSIVE_LAYERFACTORY_H
#define PELAGEIA_IMMERSIVE_LAYERFACTORY_H

#include <memory>
#include "components/scene/BaseLayer.h"
#include "utilities/CoreTypeStructs.h"

class LayerFactory {
public:
    static std::unique_ptr<BaseLayer> CreateLayer(const LayerData& layerData);
};

#endif  // PELAGEIA_IMMERSIVE_LAYERFACTORY_H
