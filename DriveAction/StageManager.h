#pragma once
#include "CircuitTrack.h"
#include "SkyDome.h"
#include <list>
/// <summary>
/// �R�[�X�̃��[�h��`��Ƃ������蔻��Ƃ�����
/// </summary>
class StageManager
{
public:
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    StageManager();

    ~StageManager();

    CircuitTrack* GetCircuit()const;
    std::string GetCheckPoint()const;
    void Draw()const;

private:
    CircuitTrack* circuit;
    SkyDome* skyDome;
    std::string checkPointAddres;
};