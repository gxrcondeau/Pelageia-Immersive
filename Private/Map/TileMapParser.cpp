//
// Created by pylinskyi.k on 07.11.2023.
//

#include <sstream>
#include <iostream>
#include <SDL_log.h>
#include "Map/TileMapParser.h"

TileMapParser* TileMapParser::s_Instance = nullptr;

bool TileMapParser::Load()
{
    return Parse("map", "Assets/Maps/map.tmx");
}

bool TileMapParser::Clean()
{
    std::map<std::string, GameMap*>::iterator iterator;
    for (iterator = m_MapDict.begin(); iterator != m_MapDict.end(); iterator++)
        iterator->second = nullptr;

    m_MapDict.clear();

    return true;
}

bool TileMapParser::Parse(std::string id, std::string source)
{
    pugi::xml_document xml;
    pugi::xml_parse_result parse_result = xml.load_file(source.c_str());
    if (parse_result.status != 0)
    {
        std::cerr << "Failed to load XML file: " << source << std::endl;
        return false;
    }

    pugi::xml_node root = xml.child("map");

    if (!root)
    {
        SDL_Log("map element not found in Tile Map XML.");
        return false;
    }

    TilesetList tilesets;
    pugi::xml_node tilesetNode = root.child("tileset");
    if (!tilesetNode)
    {
        SDL_Log("tile set element not found in Tile Map XML.");
        return false;
    }

    while (tilesetNode)
    {
        tilesets.push_back(ParseTileset(&tilesetNode));
        tilesetNode = tilesetNode.next_sibling("tileset");
    }

    int colcount, rowcount, tilesize = 0;

    tilesize = tilesets[0].TileSize;
    colcount = 100;
    rowcount = 100;

    GameMap* gamemap = new GameMap();
    pugi::xml_node layerNode = root.child("layer");
    if (!layerNode)
    {
        SDL_Log("layer element not found in Tile Map XML.");
        return false;
    }

    while (layerNode)
    {
        std::string layerName = layerNode.attribute("name").as_string();
        TileLayer* tileLayer = ParseTileLayer(&layerNode, tilesets, tilesize, rowcount, colcount);
        gamemap->m_MapLayer[layerName] = tileLayer;
        layerNode = layerNode.next_sibling("layer");
    }

    m_MapDict[id] = gamemap;

    return true;
}

Tileset TileMapParser::ParseTileset(pugi::xml_node* xmlTileset)
{
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

    pugi::xml_node tile = xmlTileset->child("tile");
    auto anim = tile.child("animation");
    auto frame = anim.child("frame");

    while (frame)
    {
        int tilegid = tileset.FirstID + frame.attribute("tileid").as_int();
        int duration = frame.attribute("duration").as_int();
        tileset.Animation.push_back(TileAnimation(tilegid, duration));
        frame = frame.next_sibling("frame");
    }

    return tileset;
}

TileLayer* TileMapParser::ParseTileLayer(pugi::xml_node* xmlTileLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount)
{
    TileMap tilemap(rowcount, std::vector<int>(colcount, 0));
    pugi::xml_node dataNode = xmlTileLayer->child("data");
    if (dataNode)
    {
        std::string encoding = dataNode.attribute("encoding").value();

        std::string csvData = dataNode.text().get();
        std::istringstream readStream(csvData);
        std::string cell;

        for (int row = 0; row < rowcount; row++)
        {
            for (int col = 0; col < colcount; col++)
            {
                std::getline(readStream, cell, ',');
                std::stringstream writeStream(cell);
                writeStream >> tilemap[row][col];

                if (!readStream.good()) break;
            }
        }
    }

    return new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets);
}
