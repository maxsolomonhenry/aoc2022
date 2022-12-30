#include <vector>
#include <array>
#include <fstream>
#include <string>
#include "util.h"
#include <algorithm>


bool isCommand(const std::string& line)
{
    return (line[0] == '$');
}

enum InputType
{
    cd,
    ls,
    info,
    unknown
};

InputType identifyInputType(const std::string& line)
{
    if (!isCommand(line))
        return InputType::info;

    if (line[2] == 'c')
        return InputType::cd;

    if (line[2] == 'l')
        return InputType::ls;

    return InputType::unknown;
}


std::string getDirName(const std::string& line)
{
    return line.substr(5, line.length());
}


struct Directory
{
    Directory* parent;
    std::string name;
    int size;
    std::vector<std::shared_ptr<Directory>> children;
};


std::shared_ptr<Directory> getDirectory(const std::string& name)
{
    std::shared_ptr dir = std::make_shared<Directory>();
    dir->name = name;
    dir->size = 0;

    return dir;
}


bool isSubDir(std::shared_ptr<Directory>& dir, const std::string& name)
{
    // TODO.
    return true;
}


void makeSubDir(std::shared_ptr<Directory>& dir, const std::string& name)
{
    // TODO.
}


std::shared_ptr<Directory> getSubDir(std::shared_ptr<Directory>& dir, const std::string& name)
{
    // TODO.
    return dir;
}


void changeDir(std::shared_ptr<Directory>& currentDir, const std::string& dirName)
{
    if (!isSubDir(currentDir, dirName))
        makeSubDir(currentDir, dirName);

    currentDir = getSubDir(currentDir, dirName);
}

int main() {

    const std::string fpath = "input/7.txt";
    std::vector<std::string> lines;

    readFile(fpath, lines);

    std::shared_ptr<Directory> currentDir = getDirectory("/");
    
    for (auto line : lines)
    {
        switch (identifyInputType(line))
        {
            case InputType::cd:
                // Get dirname.

                // If new, add as subdirectory.

                // Change to this directory.
                changeDir(currentDir, getDirName(line));

                break;
            case InputType::ls:
                break;
            case InputType::info:
                break;
            case InputType::unknown:
                std::cerr << "Unrecognized input.\n";
        }

        // Otherwise, terminal output.
    }



    return 1;
}
