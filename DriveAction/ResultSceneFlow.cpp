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

    UIData uidata = {};
    
    uidata.x = SCREEN_WIDTH / 2;
    uidata.y = SCREEN_HEIGHT / 2;
    
    //�w�i
    uidata.dataHandle = LoadGraph(resultBackImgAddress.c_str());
    backGround = new ImgUI(2.0f, uidata);

    //����
    uidata.dataHandle = CreateFontToHandle("BIZ UD�S�V�b�N", 96, 3, DX_FONTTYPE_NORMAL);
    uidata.y = UI_SCREEN_HEIGHT * 8;
    uidata.x = UI_SCREEN_WIDTH * 8;
    rankUI = new StringUI(GetColor(200,200,100), uidata);
    rankUI->UpdateString(std::to_string(ResultScore::GetPlayerRank()) + "�q�b�g������");

    switchUI = new SwitchUI();
}

ResultSceneFlow::~ResultSceneFlow()
{
    SAFE_DELETE(switchUI);
    SAFE_DELETE(rankUI);
    SAFE_DELETE(backGround);
}

void ResultSceneFlow::Update(float deltaTime)
{
    switchUI->Update(deltaTime);
    int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    if (key & PAD_INPUT_10)
    {
        isEndProccess = true;
        nextSceneType = SceneType::TITLE;
    }
}

void ResultSceneFlow::Draw()
{
    backGround->DrawUI();
    rankUI->DrawLeftAlignedString();
    switchUI->Draw();
}
