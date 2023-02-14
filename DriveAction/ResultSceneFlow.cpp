#include "ResultSceneFlow.h"
#include "StringUI.h"
#include "DxLib.h"
#include"Utility.h"
#include "ResultScore.h"
#include <iostream>
#include <string>
#include "SwitchUI.h"

ResultSceneFlow::ResultSceneFlow()
{
    backGraphHandle = LoadGraph(resultBackImgAddress.c_str());
    UIData scoreUIData = {};
    
    scoreUIData.x = SCREEN_WIDTH / 2;
    scoreUIData.y = SCREEN_HEIGHT / 2;
    scoreUIData.dataHandle=CreateFontToHandle("BIZ UDゴシック", 64, 3, DX_FONTTYPE_NORMAL);
    scoreUI = new StringUI(GetColor(200,200,100),scoreUIData);
    scoreUI->UpdateString(std::to_string(ResultScore::GetScoreTime()) + "秒でクリア");
    switchUI = new SwitchUI();
    scoreUIData.y -= SCREEN_HEIGHT / 7;
    rankUI = new StringUI(GetColor(200,200,100), scoreUIData);
    rankUI->UpdateString(std::to_string(ResultScore::GetPlayerRank())+"位！");
}

ResultSceneFlow::~ResultSceneFlow()
{
    if (backGraphHandle != -1)
    {
        DeleteGraph(backGraphHandle);
    }
    SAFE_DELETE(switchUI);
    SAFE_DELETE(scoreUI);
    SAFE_DELETE(rankUI);
}

void ResultSceneFlow::Update(float deltaTime)
{
    switchUI->Update(deltaTime);
    int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    if (key & PAD_INPUT_10)
    {
        isEndProccess = true;
    }
}

void ResultSceneFlow::Draw()
{
    DrawGraph(0, 0, backGraphHandle, false);
    scoreUI->DrawLeftAlignedString();
    rankUI->DrawRightAlignedString();
    switchUI->Draw();
}
