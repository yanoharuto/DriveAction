#include "DataAddresLoader.h"
#include <iostream>
#include <fstream>
DataAddressLoader::DataAddressLoader()
{
}

DataAddressLoader::DataAddressLoader(std::string fileName)
{
    LoadAddres(fileName);
}

DataAddressLoader::~DataAddressLoader()
{
}

std::list<std::string>::iterator DataAddressLoader::GetBeginIterator()
{
    return stringList.begin();
}

std::list<std::string>::iterator DataAddressLoader::GetEndIterator()
{
    
    return stringList.end();
}

void DataAddressLoader::LoadAddres(std::string fileName)
{
    std::ifstream ifs(fileName);
    if (!ifs)
    {
        std::cerr << "“Ç‚İ‚İ‚É¸”s" << std::endl;
        std::exit(1);
    }
    std::string charBuf;

    for (int i = 0; std::getline(ifs, charBuf); i++)
    {
        std::string backspaceChar = charBuf;
        stringList.push_back(backspaceChar);
    }
}
