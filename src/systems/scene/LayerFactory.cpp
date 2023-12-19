//
// Created by pylinskyi.k on 19.12.2023.
//

#include "systems/scene/LayerFactory.h"
#include "components/scene/TileLayer.h"
#include "components/scene/ObjectLayer.h"
#include "components/scene/CharacterLayer.h"
#include "components/scene/CollisionLayer.h"
#include "components/scene/DecorationLayer.h"
#include "components/scene/EventLayer.h"
#include "components/scene/EffectLayer.h"
#include "components/scene/OverlayLayer.h"

std::unique_ptr<BaseLayer> LayerFactory::CreateLayer(const LayerData& layerData) {
    switch (layerData.Type) {
        case LayerType::TILE: return std::make_unique<TileLayer>(layerData);
        case LayerType::OBJECT: return std::make_unique<ObjectLayer>(layerData);
        case LayerType::CHARACTER: return std::make_unique<CharacterLayer>(layerData);
        case LayerType::COLLISION: return std::make_unique<CollisionLayer>(layerData);
        case LayerType::DECORATION: return std::make_unique<DecorationLayer>(layerData);
        case LayerType::EVENT: return std::make_unique<EventLayer>(layerData);
        case LayerType::EFFECT: return std::make_unique<EffectLayer>(layerData);
        case LayerType::OVERLAY: return std::make_unique<OverlayLayer>(layerData);
        default: return nullptr;
    }
}
