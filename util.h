#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>


bool readFile(const std::string& fpath, std::vector<std::string>& lines)
{
    std::ifstream in{fpath};

    if (!in) {
        std::cerr << "Cannot open file " << fpath << std::endl;
        return false;
    }


    std::string str;
    while (std::getline(in, str)) {
        lines.push_back(str);
    }

    return true;
}