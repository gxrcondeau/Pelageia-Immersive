//
// Created by pylinskyi.k on 13.12.2023.
//

#ifndef PELAGEIA_IMMERSIVE_SPRITECOMPONENT_H
#define PELAGEIA_IMMERSIVE_SPRITECOMPONENT_H

struct Direction {
    int id;
    std::string filePath;
};

struct State {
    int id;
    int animSheetRows;
    int animSheetCols;
    int firstSpriteRow;
    int firstSpriteCol;
    int frameCount;
    int animSpeed;
    bool repeat;
    int flip;
    std::unordered_map<, Direction> directions;
};

#endif  // PELAGEIA_IMMERSIVE_SPRITECOMPONENT_H
