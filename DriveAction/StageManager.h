#pragma once
#include "CircuitTrack.h"
#include "SkyDome.h"
#include <list>
class CourceDataLoader;
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
    void Update();
    CircuitTrack* GetCircuit()const;
    void Draw()const;

private:
    CircuitTrack* circuit;
    SkyDome* skyDome;
};