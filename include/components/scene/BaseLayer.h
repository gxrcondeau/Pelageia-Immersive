//
// Created by pylinskyi.k on 19.12.2023.
//

#ifndef PELAGEIA_IMMERSIVE_BASELAYER_H
#define PELAGEIA_IMMERSIVE_BASELAYER_H

#include <vector>
#include "utilities/CoreTypeStructs.h"

class BaseLayer {
public:
    BaseLayer(const LayerData& layerData);

    virtual void Render() = 0;
    virtual void Update() = 0;

    LayerData GetLayerData() const { return _layerData; }
protected:
    LayerData _layerData;
};

#endif  // PELAGEIA_IMMERSIVE_BASELAYER_H
