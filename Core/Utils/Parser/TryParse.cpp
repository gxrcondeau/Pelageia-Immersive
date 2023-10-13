//
// Created by admin on 10/10/2023.
//

#include "TryParse.h"

std::pair<int, bool> TryParse::Int(const std::string &str) {
    int result;
    std::istringstream iss(str);
    if(iss >> result){
        return {result, true};
    } else {
        return {0, false};
    }
}

bool TryParse::Bool(const std::string &str) {
    bool result;
    std::istringstream iss(str);
    if(iss >> std::boolalpha >> result){
        return true;
    } else {
        return false;
    }
}
