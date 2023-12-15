//
// Created by pylinskyi.k on 14.12.2023.
//
#include <filesystem>
#include "systems/scene/SceneParserSystem.h"
#include "SDL_log.h"

bool SceneParserSystem::LoadMaps() {
    std::vector<std::string> gameMaps;

    for (const auto& entry : std::filesystem::directory_iterator(_gameMapsDirectory)) {
        if (entry.is_regular_file()) {
            gameMaps.push_back(entry.path().string());
        }
    }

    for (const auto gameMapXml : gameMaps){
        pugi::xml_document xml;
        pugi::xml_parse_result parse_result = xml.load_file(gameMapXml.c_str());
        if (parse_result.status != 0)
        {
            SDL_Log("Failed to load Game Map XML file: %s", gameMapXml.c_str());
            return false;
        }

        pugi::xml_node root = xml.child("map");

        if (!root)
        {
            SDL_Log("map element not found in Tile Map XML.");
            return false;
        }

        pugi::xml_node tilesetNode = root.child("tileset");
        if (!tilesetNode)
        {
            SDL_Log("tile set element not found in Tile Map XML.");
            return false;
        }

        std::vector<TilesetData> tilesets;
        while (tilesetNode)
        {
            tilesets.push_back(LoadTilest(tilesetNode));
            tilesetNode = tilesetNode.next_sibling("tileset");
        }
    }
}

TilesetData SceneParserSystem::LoadTilest(pugi::xml_node tilesetNode) {
    TilesetData tileset;
    tileset.Name = tilesetNode.attribute("name").as_string();

    tileset.FirstID = tilesetNode.attribute("firstgid").as_int();
    tileset.LastID = tileset.FirstID + tileset.TileCount - 1;

    tileset.ColCount = tilesetNode.attribute("columns").as_int();
    tileset.RowCount = tileset.TileCount / tileset.ColCount;

    tileset.TileCount = tilesetNode.attribute("tilecount").as_int();
    tileset.TileSize = tilesetNode.attribute("tilewidth").as_int();

    const auto image = tilesetNode.child("image");
    tileset.Source = image.attribute("source").as_string();

    const auto tile = tilesetNode.child("tile");
    const auto anim = tile.child("animation");
    auto frame = anim.child("frame");

    while (frame)
    {
        int tilegid = tileset.FirstID + frame.attribute("tileid").as_int();
        tileset.AnimationFrames.push_back(tilegid);
        frame = frame.next_sibling("frame");
    }

    return tileset;
}
