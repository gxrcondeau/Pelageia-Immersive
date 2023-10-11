//
// Created by admin on 10/10/2023.
//

#include "Parser.h"

std::pair<int, bool> Parser::TryParseInt(const std::string &str) {
    int result;
    std::istringstream iss(str);
    if(iss >> result){
        return {result, true};
    } else {
        return {0, false};
    }
}

bool Parser::TryParseBool(const std::string &str) {
    bool result;
    std::istringstream iss(str);
    if(iss >> std::boolalpha >> result){
        return true;
    } else {
        return false;
    }
}
