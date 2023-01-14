#pragma once
#include "StringUI.h"
#include "ImgUI.h"
class ResultSceneFlow
{
public:
    ResultSceneFlow();
    ~ResultSceneFlow();
    void Update();
    void Draw();
private:
    const std::string resultBackImgAddress = "data/result/resultGraph.png";
    int backGraphHandle;
    StringUI* scoreUI;
};

