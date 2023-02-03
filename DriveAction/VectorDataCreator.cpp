#include "VectorDataCreator.h"

VectorDataCreator::VectorDataCreator()
{
}

VectorDataCreator::VectorDataCreator(std::string setFileName)
{
    fileName = setFileName;
}

VectorDataCreator::~VectorDataCreator()
{
}

void VectorDataCreator::WriteVECTOR(VECTOR vec)
{
    writing_file.open(fileName, std::ios::app);
    std::string writing_text = std::to_string(vec.x) + ',' + std::to_string(vec.y) + ',' + std::to_string(vec.z);
    writing_file << writing_text << std::endl;
    writing_file.close();
}