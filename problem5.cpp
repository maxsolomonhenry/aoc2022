#include <vector>
#include <sstream>
#include <string>
#include "util.h"


std::vector<std::vector<char>> initStacks(const std::string& line)
{
    unsigned int numStacks = (line.length() + 1) / 4;
    std::vector<std::vector<char>> allStacks(numStacks);

    return allStacks;
}


void updateStacks(std::vector<std::vector<char>>& allStacks, const std::string& line)
{
    const int kNumCrateChars = 4;
    for (int i = 0; i < allStacks.size(); ++i)
    {
        char crateLabel = line[i * kNumCrateChars + 1];

        if (!std::isspace(crateLabel))
            allStacks[i].push_back(crateLabel);
    }
}


bool isStackLabels(const std::string& line)
{
    return (line[1] == '1');
}


std::tuple<int, int, int> parseLine(const std::string& line)
{

    std::istringstream ss(line);
    std::string token;
    std::vector<std::string> tokens;

    while(std::getline(ss, token, ' '))
    {
        tokens.push_back(token);
    }


    int numToMove = std::stoi(tokens[1]);
    int stackFrom = std::stoi(tokens[3]) - 1;
    int stackTo = std::stoi(tokens[5]) - 1;

    return {numToMove, stackFrom, stackTo};
}


int main() {

    const std::string fpath = "input/5.txt";
    std::vector<std::string> lines;
    readFile(fpath, lines);

    // Load in the crate structure.
    std::vector<std::vector<char>> allStacks;
    bool isInitialized = false;

    int lineCtr = 0;
    for (auto line : lines) 
    {
        lineCtr++;

        // Move to next phase.
        if (isStackLabels(line))
            break;

        if (!isInitialized)
        {
            allStacks = initStacks(line);
            isInitialized = true;
        }

        updateStacks(allStacks, line);
    }

    for (auto& stack : allStacks)
        std::reverse(stack.begin(), stack.end());


    // Follow instructions.
    std::vector<char> buffer;
    for (int i = lineCtr + 1; i < lines.size(); ++i)
    {
        std::string line = lines[i];

        auto [numToMove, stackFrom, stackTo] = parseLine(line);

        buffer.clear();
        for (int j = 0; j < numToMove; ++j)
        {
            char toMove = allStacks[stackFrom].back();
            allStacks[stackFrom].pop_back();

            buffer.push_back(toMove);
        }

        std::reverse(buffer.begin(), buffer.end());
        for (auto item : buffer)
        {
            allStacks[stackTo].push_back(item);
        }

    }

    for (auto stack : allStacks)
    {
        std::cout << stack.back();
    }

    return 1;
}