#include <vector>
#include <array>
#include <fstream>
#include <string>
#include <cstdlib>
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


struct Place {
    Place(int x, int y) : x(x), y(y) {}
    int x;
    int y;
};

bool operator== (const Place& a, const Place& b)
{
    return ( (a.x == b.x) && (a.y == b.y) );
}

std::ostream& operator<< (std::ostream& os, const Place& place)
{
    os << "{x: " << place.x << ", y: " << place.y << "}";
    return os;
}

class Knot {
public:

    Knot(bool isLogging = true) : isLogging(isLogging)
    {
        x = 0;
        y = 0;

        updateLog();
    }

    Place getPosition() { return Place(x, y); }
    std::vector<Place> getLog() { return log; };

    int getX() { return x; }
    int getY() { return y; }
    void setIsLogging(bool val) { isLogging = val; };

    void move(Aim aim)
    {

        switch (aim)
        {
            case Aim::left:
                x -= 1;
                break;
            case Aim::right:
                x +=1;
                break;
            case Aim::up:
                y += 1;
                break;
            case Aim::down:
                y -= 1;
                break;
            case Aim::unknown:
                std::cerr << "Unknown direction.\n"; 
                break;
        }

        updateLog();
    }
    
    void react(Knot head)
    {

        int diffX = head.getX() - x;
        int diffY = head.getY() - y;

        assert ((std::abs(diffX) <= 2) && (std::abs(diffY) <= 2) && "String snapped!");

        bool isElAway = (std::abs(diffX) + std::abs(diffY) == 3);

        // If "L" away (like a knight's move in chess), step along both axes in
        // the right direction. Otherwise, only step along a given axis if you 
        // are two away.

        if (isElAway) {
            x += sign(diffX);
            y += sign(diffY);
        } else {
            x += (std::abs(diffX) == 2) ? sign(diffX) : 0;
            y += (std::abs(diffY) == 2) ? sign(diffY) : 0;
        }

        updateLog();
    }

private:
    int x;
    int y;
    std::vector<Place> log;
    bool isLogging;

    void updateLog()
    {
        if (!isLogging)
            return;

        Place newPlace(x, y);

        for (auto place : log)
        {
            if (place == newPlace)
                return;
        }

        log.push_back(newPlace);
    }

};

std::vector<Knot> makeRope(const int& numKnots)
{
    std::vector<Knot> rope;

    for (int i = 0; i < numKnots; ++i)
        rope.emplace_back();

    return rope;
}

int main() 
{
    const std::string fpath = "input/9.txt";
    std::vector<std::string> lines;
    readFile(fpath, lines);

    const int kNumKnots = 10;
    std::vector<Knot> rope = makeRope(kNumKnots);

    rope[1].setIsLogging(true);
    rope.back().setIsLogging(true);

    for (auto line : lines)
    {
        auto [aim, numSteps] = parseInstruction(line);

        for (int i = 0; i < numSteps; ++i)
        {
            rope[0].move(aim);
            for (int j = 1; j < rope.size(); ++j)
                rope[j].react(rope[j - 1]);
        }
    }

    std::cout << "Part 1 -> Num unique spots: " << rope[1].getLog().size() << "\n";
    std::cout << "Part 2 -> Num unique spots: " << rope.back().getLog().size() << "\n";

    return 1;
}