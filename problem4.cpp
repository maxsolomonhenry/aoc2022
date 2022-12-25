#include <vector>
#include <string>
#include "util.h"


struct SectionAssignment
{
    int start;
    int end;
};


SectionAssignment stringToSectionAssignment(std::string input)
{
    // Parse by values before and after "-".
    int start = std::stoi(input.substr(0, input.find("-")));
    int end = std::stoi(input.substr(input.find("-") + 1, input.length()));

    SectionAssignment s;
    s.start = start;
    s.end = end;

    return s;
}


std::tuple<SectionAssignment, SectionAssignment> getSectionAssignments(const std::string& line)
{
    // Parse by substrings before and after ",".
    std::string aString = line.substr(0, line.find(","));
    std::string bString = line.substr(line.find(",") + 1, line.length());

    SectionAssignment a = stringToSectionAssignment(aString);
    SectionAssignment b = stringToSectionAssignment(bString);

    return {a, b};
}


bool isContainedIn(const SectionAssignment& a, const SectionAssignment& b)
{
    // Checks if a is within b.
    bool isStartContained = (a.start >= b.start);
    bool isEndContained = (a.end <= b.end);

    return (isStartContained && isEndContained);
}


int main() {

    const std::string fpath = "input/4.txt";
    std::vector<std::string> lines;
    readFile(fpath, lines);

    int ctr = 0;
    for (auto line : lines)
    {
        auto [a, b] = getSectionAssignments(line);
        
        if (isContainedIn(a, b) || isContainedIn(b, a))
            ++ctr;

    }

    std::cout << "Total count: " << ctr << "\n";

    return 1;
}