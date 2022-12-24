#include <vector>
#include <string>
#include <set>
#include "util.h"

std::tuple<std::string, std::string> splitInHalf(const std::string& line)
{
    // https://stackoverflow.com/questions/4977050/spliting-stdstring-and-a-character-array-into-two-halves-efficiently

    auto halfSize = line.length() / 2;

    std::string one = line.substr(0, halfSize);
    std::string two = line.substr(halfSize);

    return {one, two};
}


int getScore(const char& letter)
{
    int tmp = int(letter);

    // Lowercase a -- z is 1 -- 26.
    if (tmp > 96)
    {
        return tmp - 96;
    }

    // Uppercase A -- Z is 27 -- 52.
    return tmp - 38;
}


char getCommonLetter(std::set<char> one, std::set<char> two)
{
    std::vector<char> tmp;

    std::set_intersection(
        one.begin(), one.end(),
        two.begin(), two.end(),
        std::back_inserter(tmp));

    return tmp[0];
}


char getGroupCommonLetter(std::vector<std::string> groupRucksacks)
{
    std::vector<std::set<char>> sets;

    for (auto rucksack : groupRucksacks)
        sets.push_back(std::set<char>(rucksack.begin(), rucksack.end()));

    std::vector<char> commonChars;
    std::set<char> commonSet = sets[0];

    for (int i = 1; i < groupRucksacks.size(); ++i) 
    {

        std::set<char>& thisSet = sets[i];

        std::set_intersection(
            thisSet.begin(), thisSet.end(),
            commonSet.begin(), commonSet.end(),
            std::back_inserter(commonChars));

        commonSet = std::set<char>(commonChars.begin(), commonChars.end());
        commonChars.clear();
    }

    // Return only element in the set.
    return *commonSet.begin();
}


int main() {

    const int kNumElvesPerGroup = 3;

    const std::string fpath = "input/3.txt";

    std::vector<std::string> lines;
    readFile(fpath, lines);

    int totalSum = 0;
    std::vector<std::string> groupRucksacks;
    for (auto line : lines)
    {
        groupRucksacks.push_back(line);

        if (groupRucksacks.size() < kNumElvesPerGroup)
            continue;

        char commonLetter = getGroupCommonLetter(groupRucksacks);
        totalSum += getScore(commonLetter);

        groupRucksacks.clear();

    }

    std::cout << "Total sum: " << totalSum << "\n";

    return 1;
}