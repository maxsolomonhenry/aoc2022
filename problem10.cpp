#include <vector>
#include <string>
#include "util.h"

std::tuple<int, int> parseInstruction(const std::string& line)
{
    int numCycles;
    int valToAdd;

    std::string instruction = line.substr(0, line.find(' '));

    if (instruction == "noop") {
        numCycles = 1;
        valToAdd = 0;
    } else if (instruction == "addx") {
        numCycles = 2;
        valToAdd = std::stoi(line.substr(line.find(' ') + 1));
    } else {
        throw std::invalid_argument("Expected either 'noop' or 'addx'.");
    }

    return {numCycles, valToAdd};
}

int main() 
{
    std::vector<std::string> lines;
    readFile("input/10.txt", lines);

    int totalStrength = 0;
    int ctrCycles = 0;
    int rx = 1;

    for (auto line : lines) {
        auto [numCycles, valToAdd] = parseInstruction(line);

        for (int i = 0; i < numCycles; ++i)
        {
            ctrCycles++;

            if ((ctrCycles % 40) - 20 == 0) {
                std::cout << "ctrCycles: " << ctrCycles << "\n";
                totalStrength += ctrCycles * rx;
            }

        }
        
        rx += valToAdd;
    }

    std::cout << "totalStrength: " << totalStrength << "\n";

    return 0;
}