#include <vector>
#include <array>
#include <fstream>
#include <string>
#include "util.h"

int main() 
{
    const std::string fpath = "input/9.txt";
    std::vector<std::string> lines;
    readFile(fpath, lines);

    return 1;
}