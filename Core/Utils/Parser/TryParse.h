//
// Created by admin on 10/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_TRYPARSE_H
#define PELAGEIA_IMMERSIVE_TRYPARSE_H


#include <iostream>
#include <string>
#include <sstream>
#include <utility>

class TryParse {
public:
    std::pair<int, bool> static Int(const std::string& str);
    bool static Bool(const std::string& str);
};


#endif //PELAGEIA_IMMERSIVE_TRYPARSE_H
