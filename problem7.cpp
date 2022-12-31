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


class Directory : public std::enable_shared_from_this<Directory>
{
public:
    Directory(const std::string& name) : name(name) 
    {
        parent = nullptr;
        size = 0;
    }

    std::shared_ptr<Directory> getSubDir(const std::string& name)
    {
        std::shared_ptr<Directory> subdir = findSubDir(name);

        if (subdir != nullptr)
            return subdir;
        else
            return makeSubDir(name);
    }

    std::shared_ptr<Directory> getParent()
    {
        return parent;
    }

    std::vector<std::shared_ptr<Directory>> getChildren()
    {
        return children;
    }

    std::string getName()
    {
        return name;
    }

    int getSize()
    {
        return size;
    }

    void addFileSize(int size)
    {
        this->size += size;

        if (parent != nullptr)
        {
            parent->addFileSize(size);
        }
    }

    void print()
    {
        std::cout << "Name:\t" << name << "\n";
        std::cout << "Size:\t" << size << "\n";
        std::cout << "\n";

        if (!children.empty())
        {
            for (auto child : children)
                child->print();
        }
    }

private:
    std::string name;
    int size;
    std::shared_ptr<Directory> parent;
    std::vector<std::shared_ptr<Directory>> children;

    std::shared_ptr<Directory> findSubDir(const std::string& name) 
    {
        for (auto child : children)
        {
            if (child->name == name)
                return child;
        }

        return nullptr;
    }

    std::shared_ptr<Directory> makeSubDir(const std::string& name)
    {
        auto subdir = std::make_shared<Directory>(name);
        subdir->parent = shared_from_this();
        children.push_back(subdir);
        return subdir;
    }

};


int getFileSize(const std::string& line)
{
    std::string tmp = line.substr(0, line.find(" "));

    if (tmp == "dir")
        return 0;
    else
        return std::stoi(tmp);
}


int solve(std::shared_ptr<Directory> root)
{
    const int kSizeLimit = 100000;

    int totalSize = 0;
    for (auto child : root->getChildren())
    {
        if (child->getSize() <= kSizeLimit)
            totalSize += child->getSize();

        totalSize += solve(child);
    }

    return totalSize;
}



int main() {

    const std::string fpath = "input/7.txt";
    std::vector<std::string> lines;

    readFile(fpath, lines);

    auto root = std::make_shared<Directory>("/");
    auto currentDir = root;
    std::string dirName;
    int size;

    for (auto line : lines)
    {
        switch (identifyInputType(line))
        {
            case InputType::cd:
                dirName = getDirName(line);

                if (dirName == "..")
                    currentDir = currentDir->getParent();
                else
                    currentDir = currentDir->getSubDir(dirName);
                break;

            case InputType::ls:
                // Nothing to do.
                break;

            case InputType::info:
                size = getFileSize(line);
                currentDir->addFileSize(size);
                break;

            case InputType::unknown:
                std::cerr << "Unrecognized input.\n";
        }
    }

    std::cout << "Answer: " << solve(root) << "\n";
    return 1;
}