//
// Created by pylinskyi.k on 13.12.2023.
//

#ifndef PELAGEIA_IMMERSIVE_ISOMETRICCONVERTER_H
#define PELAGEIA_IMMERSIVE_COORDINATES_H

#include <cmath>

static class Coordinates
{
public:
    static const int tileSize = 32;
    static int GetIsoX(int row, int col) { return (col - row) * (tileSize / 2); }
    static int GetIsoY(int row, int col) { return (col + row) * (tileSize / 4); }
    static int GetIsoRow(int x, int y) { return static_cast<int>(std::round((2.0 * y + x) / tileSize)); }
    static int GetIsoCol(int x, int y) { return static_cast<int>(std::round((2.0 * y - x) / tileSize)); }
};

#endif  // PELAGEIA_IMMERSIVE_ISOMETRICCONVERTER_H
