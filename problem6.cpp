#include <vector>
#include <array>
#include <fstream>
#include <string>
#include "util.h"
#include <algorithm>

class CircularBuffer {
public:
    CircularBuffer(int size)
    {
        for (int i = 0; i < size; ++i)
            buffer += ".";
        ptr = 0;
        
        sortedBuffer = buffer;
    }

    void write(char input)
    {
        buffer[ptr] = input;
        ptr = (ptr + 1) % buffer.size();
    }

    std::string read()
    {
        return buffer;
    }

    bool contains(char query)
    {
        return (buffer.find(query) != std::string::npos);
    }

    bool isAllUnique()
    {
        // Copy into sorting buffer.
        sortedBuffer = buffer;

        std::sort(sortedBuffer.begin(), sortedBuffer.end());

        // Check for two consecutive chars that are the same.
        char lastChar = '.';
        for (char thisChar : sortedBuffer)
        {
            if (thisChar == lastChar)
                return false;
            
            lastChar = thisChar;
        }

        return true;
    }

private:
    int ptr;
    std::string buffer;
    std::string sortedBuffer;

};

int main() {

    const std::string fpath = "input/6.txt";

    char ch;
    std::fstream fin(fpath, std::fstream::in);
    CircularBuffer buffer(14);

    int charCtr = 0;

    // Read file one char at a time.
    while (fin >> std::noskipws >> ch)
    {
        buffer.write(ch);
        charCtr++;

        if (buffer.contains('.'))
            continue;

        if (buffer.isAllUnique())
        {
            std::cout << "Start-of-packet: " << charCtr << "\n";
        }
    }

    return 1;
}
