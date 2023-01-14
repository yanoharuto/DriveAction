#include "ResultSceneFlow.h"
#include "StringUI.h"
#include "DxLib.h"
#include"Utility.h"
#include "ScoreTime.h"
#include <iostream>
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
    scoreUIData.dataHandle=CreateFontToHandle("BIZ UDƒSƒVƒbƒN", 64, 3, DX_FONTTYPE_NORMAL);
    scoreUI = new StringUI(GetColor(200,200,200),scoreUIData);
    float scoreTime = ScoreTime::GetScoreTime();
    std::string scoreTimeStr = scoreTime;
    scoreUI->Update(scoreTimeStr);
}

ResultSceneFlow::~ResultSceneFlow()
{
    if (backGraphHandle != -1)
    {
        DeleteGraph(backGraphHandle);
    }
}

void ResultSceneFlow::Update()
{
    
}

void ResultSceneFlow::Draw()
{
    DrawGraph(0, 0, backGraphHandle, false);
    scoreUI->DrawUI();
}
