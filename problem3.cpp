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


int main() {

    const std::string fpath = "input/3.txt";

    std::vector<std::string> lines;
    readFile(fpath, lines);

    int totalSum = 0;
    for (auto line : lines)
    {
        auto [one, two] = splitInHalf(line);

        std::set<char> uniqueOne(one.begin(), one.end());
        std::set<char> uniqueTwo(two.begin(), two.end());

        char commonLetter = getCommonLetter(uniqueOne, uniqueTwo);
        
        totalSum += getScore(commonLetter);
    }

    std::cout << "Total sum: " << totalSum << "\n";

    return 1;
}