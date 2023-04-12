#pragma once
#include <vector>
#include <string>
class CSVFileLoader
{
public:
    CSVFileLoader(std::string fileName);
    ~CSVFileLoader();
    std::vector <std::string> GetLoadData();
    int GetLineCount();
private:
    void Split(std::string& input, char delimiter);
    std::vector <std::string> loadData;
    int lineCount;
};

