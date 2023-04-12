#include "CSVFileLoader.h"
#include <fstream>
#include <sstream>

using namespace std;
CSVFileLoader::CSVFileLoader(std::string fileName)
{
    lineCount = 0;
    ifstream ifs(fileName.c_str());

    string line;
    while (getline(ifs, line)) 
    {
        lineCount++;
        Split(line, ',');
    }

}

CSVFileLoader::~CSVFileLoader()
{
}

std::vector<std::string> CSVFileLoader::GetLoadData()
{
    return loadData;
}

int CSVFileLoader::GetLineCount()
{
    return lineCount;
}

void CSVFileLoader::Split(std::string& input, char delimiter)
{
    istringstream stream(input);
    string field;
    while (getline(stream, field, delimiter)) {
        loadData.push_back(field);
    }
}
