#pragma once
#include <string>
#include <fstream>
#include "DxLib.h"
class VectorDataCreator
{
public:
    VectorDataCreator();
    VectorDataCreator(std::string setFileName);
    ~VectorDataCreator();
    void WriteVECTOR(VECTOR vec);
private:
    std::ofstream writing_file;
    std::string fileName;
};

