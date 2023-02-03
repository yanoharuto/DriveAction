#pragma once
#include "StringUI.h"
#include "ImgUI.h"
#include "SwitchUI.h"
#include <string>
class ResultSceneFlow
{
public:
    ResultSceneFlow();
    ~ResultSceneFlow();
    void Update(float deltaTime);
    bool IsProccssEnd();
    void Draw();
private:
    const std::string resultBackImgAddress = "data/result/resultGraph.png";
    int backGraphHandle;
    StringUI* scoreUI;
    SwitchUI* switchUI;
    bool isProccessEnd;
};

