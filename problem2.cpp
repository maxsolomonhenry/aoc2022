#include <vector>
#include <iostream>
#include <string>
#include <tuple>
#include "util.h"


enum Shape {
    rock,
    paper,
    scissors,
    unknown
};

Shape charToShape(const char& c)
{
    switch (c) 
    {
        case 'A':
            return Shape::rock;
        case 'B':
            return Shape::paper;
        case 'C':
            return Shape::scissors;
    }

    return Shape::unknown;
}

Shape getLoser(const Shape& theirShape)
{
    switch (theirShape)
    {
        case Shape::rock:
            return Shape::scissors;
        case Shape::paper:
            return Shape::rock;
        case Shape::scissors:
            return Shape::paper;
    }
}


Shape getWinner(const Shape& theirShape)
{
    switch (theirShape)
    {
        case Shape::rock:
            return Shape::paper;
        case Shape::paper:
            return Shape::scissors;
        case Shape::scissors:
            return Shape::rock;
    }
}


Shape getInstrucedShape(const Shape& theirShape, const char& instruction)
{
    switch (instruction)
    {
        case 'X':
            return getLoser(theirShape);
        case 'Y':
            return theirShape;
        case 'Z':
            return getWinner(theirShape);
    }
}

std::tuple<Shape, Shape> getShapes(const std::string& line) 
{

    Shape theirShape = charToShape(line[0]);
    Shape myShape = getInstrucedShape(theirShape, line[2]);

    return {myShape, theirShape};
}


bool isWin(const char& myShape, const char& theirShape)
{
    bool isWinRock = (myShape == Shape::rock && theirShape == Shape::scissors);
    bool isWinPaper = (myShape == Shape::paper && theirShape == Shape::rock);
    bool isWinScissors = (myShape == Shape::scissors && theirShape == Shape::paper);

    return (isWinRock || isWinPaper || isWinScissors);
}


int getShapeBonus(const Shape& myShape)
{
    switch (myShape)
    {
        case Shape::rock:
            return 1;
        case Shape::paper:
            return 2;
        case Shape::scissors:
            return 3;
        default:
            std::cerr << "Unrecognized shape.\n";
    }
}


int main() {

    const std::string fpath = "input/2.txt";
    std::vector<std::string> lines;

    readFile(fpath, lines);

    // The scoring rules.
    const int kNumDrawPoints = 3;
    const int kNumWinPoints = 6;

    int score = 0;
    for (auto line : lines)
    {
        auto [myShape, theirShape] = getShapes(line);
        score += getShapeBonus(myShape);

        if (myShape == theirShape)
        {
            score += kNumDrawPoints;
            continue;
        }

        if (isWin(myShape, theirShape))
        {
            score += kNumWinPoints;
        }
    }

    std::cout << "Total score: " << score << "\n";

     return 1;
}