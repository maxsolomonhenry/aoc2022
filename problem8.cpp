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

int main() 
{
    const std::string fpath = "input/8.txt";
    std::vector<std::string> lines;

    readFile(fpath, lines);

    auto map = makeIntMap(lines);

    auto topview = makeVisibilityMap(map, Viewpoint::top);
    auto bottomview = makeVisibilityMap(map, Viewpoint::bottom);
    auto leftview = makeVisibilityMap(map, Viewpoint::left);
    auto rightview = makeVisibilityMap(map, Viewpoint::right);
    
    // Make "visible from {left, right, up, down}" maps.
    // Combine maps with `or`.

    return 1;
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

// Viewpoint getReverseView(Viewpoint view)
// {
//     switch (view)
//     {
//         case Viewpoint::bottom:
//             return Viewpoint::top;
//         case Viewpoint::top:
//             return Viewpoint::bottom;
//         case Viewpoint::left:
//             return Viewpoint::right;
//         case Viewpoint::right:
//             return Viewpoint::left;
//     }
// }


template<typename T>
std::vector<std::vector<T>> makeEmptyMap(const int& numRows, const int& numCols)
{
    std::vector<std::vector<T>> output;
    std::vector<T> tmp;
    tmp.resize(numCols);

    for (int r = 0; r < numRows; ++r)
        output.push_back(tmp);

    return output;
}


template <typename T>
void rotate(std::vector<std::vector<T>>& map, Viewpoint view)
{

    const int numRows = map.size();
    const int numCols = map[0].size();
    std::vector<std::vector<T>> newMap;

    switch (view)
    {
        case Viewpoint::top:
            // Transpose dimensions.
            newMap = makeEmptyMap(numCols, numRows);
            // TODO... fill.
            break;
        case Viewpoint::bottom:
            // Transpose dimensions.
            newMap = makeEmptyMap(numCols, numRows);
            // TODO... fill, flip etc.
            break;
        case Viewpoint::left:
            // Do nothing.
            break;
        case Viewpoint::right:
            for (auto& row : map)
                std::reverse(row.begin(), row.end());
            break;
    }
}

std::vector<std::vector<bool>> makeVisibilityMap(std::vector<std::vector<int>> map, Viewpoint view)
{

    rotate<int>(map, view);

    int maxHeight;
    bool isVisible;
    std::vector<std::vector<bool>> visibilityMap;
    std::vector<bool> tmp;

    const int numRows = map.size();
    const int numCols = map[0].size();

    for (int r = 0; r < numRows; ++r)
    {   
        tmp.clear();
        // Guarantee all edge trees are "visible,"" even if 0.
        maxHeight = -1;

        for (int c = 0; c < numCols; ++c)
        {
            isVisible = (map[r][c] > maxHeight);

            tmp.push_back(isVisible);

            if (isVisible)
                maxHeight = map[r][c];
        }

        visibilityMap.push_back(tmp);
    }

    rotate<bool>(visibilityMap, view);

    return visibilityMap;
}