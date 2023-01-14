#include "ResultSceneFlow.h"
#include "StringUI.h"
#include "DxLib.h"
#include"Utility.h"
#include "ScoreTime.h"
#include <iostream>
#include <string>
#include "SwitchUI.h"

ResultSceneFlow::ResultSceneFlow()
{
    backGraphHandle = LoadGraph(resultBackImgAddress.c_str());
    UIData scoreUIData = {};
    float x = SCREEN_WIDTH;
    x /=  2;
    float y = SCREEN_HEIGHT;
    y /= 2;
    scoreUIData.x = x;
    scoreUIData.y = y;
    scoreUIData.dataHandle=CreateFontToHandle("BIZ UDゴシック", 64, 3, DX_FONTTYPE_NORMAL);
    scoreUI = new StringUI(GetColor(200,200,100),scoreUIData);
    scoreUI->Update(std::to_string(ScoreTime::GetScoreTime())+"秒でクリア");
    switchUI = new SwitchUI();
}

ResultSceneFlow::~ResultSceneFlow()
{
    if (backGraphHandle != -1)
    {
        DeleteGraph(backGraphHandle);
    }
    SAFE_DELETE(switchUI);
}

void ResultSceneFlow::Update(float deltaTime)
{
    switchUI->Update(deltaTime);
}

void ResultSceneFlow::Draw()
{
    DrawGraph(0, 0, backGraphHandle, false);
    scoreUI->DrawUI();
    switchUI->Draw();
}
