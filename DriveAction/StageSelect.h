#pragma once
#include <list>
#include <string>

class StageSelect
{
public:
    StageSelect();
    ~StageSelect();
    void ChangeStage(bool up);
    void LoadeStage();
private:
    std::list<std::string> stageFileNameList;
    std::list<std::string>::iterator fileNameIte;
};

