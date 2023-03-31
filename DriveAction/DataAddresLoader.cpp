#include "DataAddresLoader.h"
#include <iostream>
#include <fstream>
DataPassLoader::DataPassLoader()
{
}

DataPassLoader::DataPassLoader(std::string fileName)
{
    LoadAddres(fileName);
}

DataPassLoader::~DataPassLoader()
{
}

std::list<std::string>::iterator DataPassLoader::GetBeginIterator()
{
    return stringList.begin();
}

std::list<std::string>::iterator DataPassLoader::GetEndIterator()
{
    
    return stringList.end();
}

void DataPassLoader::LoadAddres(std::string fileName)
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
        stringList.push_back(backspaceChar);
    }
}
