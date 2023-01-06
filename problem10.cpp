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
    int registerX = 1;

    int spritePosition = 0;
    bool isDrawing = false;
    std::string outputBuffer;
    char pixel;

    for (auto line : lines) {
        auto [numCycles, valToAdd] = parseInstruction(line);

        for (int i = 0; i < numCycles; ++i) {

            isDrawing = (
                (spritePosition == registerX) || 
                (spritePosition == (registerX - 1)) ||
                (spritePosition == (registerX + 1))
            );

            pixel = isDrawing ? '#' : '.';
            outputBuffer += pixel;

            ctrCycles++;
            spritePosition = (ctrCycles % 40);

            if (spritePosition == 39){
                std::cout << outputBuffer << "\n";
                outputBuffer.clear();
            }

            // Part 1.
            if ((ctrCycles % 40) - 20 == 0)
                totalStrength += ctrCycles * registerX;
        }

        registerX += valToAdd;
    }

    std::cout << "(Part 1) totalStrength: " << totalStrength << "\n";

    return 0;
}


