#pragma once
#include <string>
#include <list>
#include "DxLib.h"
#include "UIDataStruct.h"
#include "Utility.h"
#include "ObjPosAndDir.h"
class MiniMap
{
public:
    MiniMap();
    ~MiniMap();
    void Update(ObjInfo objInfo,std::list<VECTOR> setCoinPosList);
    void Draw();
private:
    VECTOR ConvertPosition(VECTOR pos);
    //�v���C���[�̃}�[�J�[�̐F
    const unsigned int playerColor = GetColor(255,0,0);
    //���W���̐F
    const unsigned int coinColor = GetColor(200,0,200);
    //�}�b�v�̕�
    const float mapRength = 100.0f;
    //map�̕`�撆�S���W
    const int miniMapFrontX = UI_SCREEN_WIDTH * 17;
    //map�̕`�撆�S���W
    const int miniMapFrontY = UI_SCREEN_HEIGHT * 13;
    //�`��J�n����X���W
    const int miniMapUpLeftX = miniMapFrontX - mapRength;
    //�`��J�n����Y���W
    const int miniMapUpLeftY = miniMapFrontY - mapRength;
    
    //�~�j�}�b�v�̉摜�̉���
    int mapGraphWidth = 0;
    //�~�j�}�b�v�̉摜�̏c��
    int mapGraphHeight = 0;

    //�~�j�}�b�v�̉摜�̃A�h���X
    const std::string miniMapPass = "data/miniMap.png";
    //���@��Icon�̑傫��
    const float iconSize = 5.0f;
    //�~�j�}�b�v
    UIData miniMap;
    //���@�̃A�C�R��
    UIData icon;

    std::list<VECTOR> coinPosList;
};