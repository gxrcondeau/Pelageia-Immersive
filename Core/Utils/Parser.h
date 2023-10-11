//
// Created by admin on 10/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_PARSER_H
#define PELAGEIA_IMMERSIVE_PARSER_H


#include <iostream>
#include <string>
#include <sstream>
#include <utility>

class Parser {
public:
    std::pair<int, bool> static TryParseInt(const std::string& str);
    bool static TryParseBool(const std::string& str);
};


#endif //PELAGEIA_IMMERSIVE_PARSER_H
