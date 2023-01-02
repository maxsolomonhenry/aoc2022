#include <vector>
#include <array>
#include <fstream>
#include <string>
#include "util.h"


enum Aim {
    up,
    down,
    left,
    right,
    unknown
};

Aim charToAim(const char& input)
{
    switch (input) {
        case 'U':
            return Aim::up;
        case 'D':
            return Aim::down;
        case 'L':
            return Aim::left;
        case 'R':
            return Aim::right;
        default:
            return Aim::unknown;
    }
}

std::tuple<Aim, int> parseInstruction(const std::string& line)
{
    Aim aim = charToAim(line[0]);
    int numSteps = std::stoi(line.substr(line.find(' ') + 1));

    return {aim, numSteps};
}

int main() 
{
    const std::string fpath = "input/9.txt";
    std::vector<std::string> lines;
    readFile(fpath, lines);

    for (auto line : lines)
    {
        auto [aim, numSteps] = parseInstruction(line);

        std::cout << "aim: " << aim << " numsteps: " << numSteps << "\n";
    }

    return 1;
}