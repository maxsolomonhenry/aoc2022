#include <vector>
#include <string>
#include "util.h"

int main() {

    // Parameters.
    int numTopElves = 3;
    const std::string fpath = "input/1.txt";

    std::vector<std::string> lines;

    readFile(fpath, lines);

    std::vector<int> caloriesPerElf;

    int numCalories = 0;
    for (auto line : lines)
    {
        if (line.empty()) {
            caloriesPerElf.push_back(numCalories);
            numCalories = 0;
            continue;
        }

        numCalories += std::stoi(line);
    }

    std::sort(caloriesPerElf.begin(), caloriesPerElf.end(), std::greater<int>());

    int sumCaloriesTopElves = 0;
    for (int i = 0; i < numTopElves; ++i)
    {
        sumCaloriesTopElves += caloriesPerElf[i];
    }

    std::cout << sumCaloriesTopElves;

    return 1;
}