#include <vector>
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
    for (int i = lineCtr + 1; i < lines.size(); ++i)
    {
        std::string line = lines[i];
        
        std::cout << line << "\n";
    }

    return 1;
}