//
// Created by pylinskyi.k on 07.11.2023.
//

#include "MapParser.h"

bool MapParser::Load() {
    return Parse("level", "Assets/Maps/map.tmx");

}

bool MapParser::Clean() {
    return false;
}

bool MapParser::Parse(std::string id, std::string source) {
    return false;
}

Tileset MapParser::ParseTileset(TiXmlElement *xmlTileset) {
    Tileset tileset;
    tileset.Name = xmlTileset->Attribute("name");
    xmlTileset->Attribute("firstgid", &tileset.FirstID);

    xmlTileset->Attribute("tilecount", &tileset.TileCount);
    tileset.LastID = tileset.FirstID + tileset.TileCount - 1;

    xmlTileset->Attribute("columns", &tileset.ColCount);
    tileset.RowCount = tileset.TileCount / tileset.ColCount;

    xmlTileset->Attribute("tilewidth", &tileset.TileSize);

    TiXmlElement* image = xmlTileset->FirstChildElement();
    tileset.Source = image->Attribute("source");
    return tileset;

}
