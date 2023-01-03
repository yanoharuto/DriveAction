#include "CircuitDataLoader.h"
#include <iostream>
#include <fstream>
CircuitDataLoader::CircuitDataLoader()
{
}

CircuitDataLoader::~CircuitDataLoader()
{
}

void CircuitDataLoader::GetString(std::list<std::string>* stringList, std::string fileName)
{
    std::ifstream ifs(fileName);
        if (!ifs)
    {
        std::cerr << "“Ç‚Ýž‚Ý‚ÉŽ¸”s" << std::endl;
        std::exit(1);
    }
    std::string charBuf;

    for (int i = 0; std::getline(ifs, charBuf); i++)
    {
        std::string backspaceChar = charBuf;
        stringList->push_back(backspaceChar);
    }
}
