#pragma once
#include <string>
#include <list>
#include <map>
#include "DxLib.h"
/// <summary>
/// �����������ɂ��Ă̍\����
/// </summary>
struct SoundsGenerated
{
    bool isGenerated;
    std::map<std::string,int> soundAddress;//���̑f�ނ̏ꏊ
    std::list<std::string> stopSoundAddress;//�~�߂鉹
    VECTOR soundPosition;//�������������ꏊ
};