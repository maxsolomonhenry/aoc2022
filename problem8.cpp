#include <vector>
#include <array>
#include <fstream>
#include <string>
#include "util.h"


enum Viewpoint
{
    top,
    bottom,
    left,
    right
};

std::vector<std::vector<int>> makeIntMap(const std::vector<std::string>&);
std::vector<std::vector<bool>> makeVisibilityMap(std::vector<std::vector<int>>, Viewpoint);
Viewpoint getReverseView(Viewpoint);
void rotate(std::vector<std::vector<int>>&, Viewpoint);
void print(std::vector<std::vector<bool>>);
int getScenicScore(const std::vector<std::vector<int>>&, int, int);

int main() 
{
    const std::string fpath = "input/8.txt";
    std::vector<std::string> lines;

    readFile(fpath, lines);

    auto map = makeIntMap(lines);

    // Part 1.
    auto topview = makeVisibilityMap(map, Viewpoint::top);
    auto bottomview = makeVisibilityMap(map, Viewpoint::bottom);
    auto leftview = makeVisibilityMap(map, Viewpoint::left);
    auto rightview = makeVisibilityMap(map, Viewpoint::right);
    
    int ctr = 0;

    int numRows = map.size();
    int numCols = map[0].size();

    for (int r = 0; r < numRows; ++r)
    {
        for (int c = 0; c < numCols; ++c)
        {
            bool isVisible = (
                topview[r][c] || 
                bottomview[r][c] || 
                leftview[r][c] || 
                rightview[r][c]
            );

            if (isVisible)
                ctr++;
        }
    }

    std::cout << "Num visible trees: " << ctr << "\n";

    // Part 2.

    int maxScore = 0;
    int thisScore;

    for (int x = 0; x < numRows; ++x)
    {
        for (int y = 0; y < numCols; ++y)
        {
            thisScore = getScenicScore(map, x, y);

            if (thisScore > maxScore)
                maxScore = thisScore;
        }
    }

    std::cout << "Max scenic score: " << maxScore << "\n";

    return 1;
}


int getScenicScore(const std::vector<std::vector<int>>& map, int x, int y)
{

    int numRows = map.size();
    int numCols = map[0].size();

    bool isEdge = (x == 0 || y == 0 || x == (numRows - 1) || y == (numCols - 1));

    if (isEdge)
        return 0;

    int top = 0;
    int bottom = 0;
    int left = 0;
    int right = 0;

    int centerHeight = map[x][y];

    // Top.
    for (int r = x - 1; r >= 0; --r)
    {
        top++;

        int thisHeight = map[r][y];
        if (thisHeight >= centerHeight)
            break;
    }

    // Bottom.
    for (int r = x + 1; r < numRows; ++r)
    {
        int thisHeight = map[r][y];
        bottom++;

        if (thisHeight >= centerHeight)
            break;
    }

    // Left.
    for (int c = y - 1; c >= 0; --c)
    {
        int thisHeight = map[x][c];
        left++;

        if (thisHeight >= centerHeight)
            break;
    }


    // Right.
    for (int c = y + 1; c < numCols; ++c)
    {
        int thisHeight = map[x][c];
        right++;

        if (thisHeight >= centerHeight)
            break;
    }

    return (top * bottom * left * right);

}


void print(std::vector<std::vector<bool>> visibilityMap)
{
    for (auto line : visibilityMap)
    {
        for (auto element : line)
        {
            std::cout << (element ? 1 : 0);
        }
        std::cout << "\n";
    }
}


std::vector<std::vector<int>> makeIntMap(const std::vector<std::string>& lines) 
{
    std::vector<std::vector<int>> map;

    for (auto line : lines)
    {
        std::vector<int> tmp;

        for (char c : line)
        {
            tmp.push_back(ctoi(c));
        }

        map.push_back(tmp);
    }

    return map;
}


template <typename T>
std::vector<std::vector<T>> makeBlankMap(const int& numRows, const int& numCols)
{
    std::vector<std::vector<T>> output;
    std::vector<T> tmp;
    
    for (int c = 0; c < numCols; ++c)
        tmp.push_back(0);

    for (int r = 0; r < numRows; ++r)
        output.push_back(tmp);

    return output;
}


std::vector<std::vector<bool>> makeVisibilityMap(std::vector<std::vector<int>> map, Viewpoint view)
{
    int maxHeight;
    bool isVisible;

    const int numRows = map.size();
    const int numCols = map[0].size();
    std::vector<std::vector<bool>> visibilityMap = makeBlankMap<bool>(numRows, numCols);

    bool isVertical = (view == Viewpoint::bottom || view == Viewpoint::top);

    int iLimit = isVertical ? numCols : numRows;
    int jLimit = isVertical ? numRows : numCols;

    if (view == Viewpoint::bottom)
        std::reverse(map.begin(), map.end());

    for (int i = 0; i < iLimit; ++i)
    {   
        if (view == Viewpoint::right)
            std::reverse(map[i].begin(), map[i].end());

        // Guarantee all edge trees are "visible," even if 0.
        maxHeight = -1;

        for (int j = 0; j < jLimit; ++j)
        {
            int& element = (isVertical ? map[j][i] : map[i][j]);
            // bool &outElement = (isVertical ? visibilityMap[j][i] : visibilityMap[i][j]);

            isVisible = (element > maxHeight);

            if (isVertical)
                visibilityMap[j][i] = isVisible;
            else
                visibilityMap[i][j] = isVisible;

            if (isVisible)
                maxHeight = element;
        }

        if (view == Viewpoint::right)
            std::reverse(visibilityMap[i].begin(), visibilityMap[i].end());
    }

    if (view == Viewpoint::bottom)
        std::reverse(visibilityMap.begin(), visibilityMap.end());

    return visibilityMap;
}