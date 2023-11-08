//
// Created by pylinskyi.k on 07.11.2023.
//

#include <sstream>
#include <iostream>
#include "MapParser.h"

bool MapParser::Load() {
    return Parse("level", "Assets/Maps/map.tmx");

}

bool MapParser::Clean() {
    return false;
}

bool MapParser::Parse(std::string id, std::string source) {
    pugi::xml_document xml;
    pugi::xml_parse_result parse_result = xml.load_file(source.c_str());
    if(parse_result.status != 0) {
        std::cerr << "Failed to load XML file: " << source << std::endl;
        return false;
    }

    pugi::xml_node root = xml.root();
    int colcount, rowcount, tilesize = 0;

    tilesize = root.attribute("tileWidth").as_int();
    colcount = root.attribute("width").as_int();
    rowcount = root.attribute("height").as_int();

    TilesetList tilesets;
    for(pugi::xml_node e = root.first_child(); e != nullptr; e = e.next_sibling()){
        if(e.value() == std::string("tileset")){
            tilesets.push_back(ParseTileset(&e));
        }
    }

    GameMap* gamemap = new GameMap();
    for(pugi::xml_node e = root.first_child(); e != nullptr; e = e.next_sibling()){
        if(e.value() == std::string("layer")){
            TileLayer* tileLayer = ParseTileLayer(&e, tilesets, tilesize, colcount, rowcount);
            gamemap->m_MapLayer.push_back(tileLayer);
        }
    }

    m_MapDict[id] = gamemap;
}

Tileset MapParser::ParseTileset(pugi::xml_node* xmlTileset) {
    Tileset tileset;
    tileset.Name = xmlTileset->attribute("name").as_string();
    tileset.FirstID = xmlTileset->attribute("firstgid").as_int();

    tileset.TileCount = xmlTileset->attribute("tilecount").as_int();
    tileset.LastID = tileset.FirstID + tileset.TileCount - 1;

    tileset.ColCount = xmlTileset->attribute("columns").as_int();
    tileset.RowCount = tileset.TileCount / tileset.ColCount;

    tileset.TileSize = xmlTileset->attribute("tilewidth").as_int();

    pugi::xml_node image = xmlTileset->child("image");
    tileset.Source = image.attribute("source").as_string();

    return tileset;
}

TileLayer *MapParser::ParseTileLayer(pugi::xml_node *xmlTileLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount) {
    pugi::xml_node data;

    for(pugi::xml_node e = xmlTileLayer->first_child(); e != nullptr; e = e.next_sibling()){
        if(e.value() == std::string("data")){
            data = e;
            break;
        }
    }

    std::string matrix(data.value());
    std::istringstream iss(matrix);
    std::string id;

    TileMap tilemap(rowcount, std::vector<int>(colcount, 0));

    for(int row = 0; row = rowcount; row++){
        for(int col = 0; col = colcount; col++){
            std::getline(iss, id, ',');
            std::stringstream convertor(id);
            convertor >> tilemap[row][col];

            if(!iss.good()) break;
        }
    }

    return new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets);
}

