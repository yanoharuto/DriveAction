#pragma once
#include <list>
#include <string>
class CircuitDataLoader
{
public:
    CircuitDataLoader();
    ~CircuitDataLoader();
    void GetString(std::list <std::string>* stringList, std::string fileName);
};

