#pragma once
#include "Stage.h"
/// <summary>
/// �X�J�C�h�[��
/// </summary>
class SkyDome final :public Stage
{
public:
    /// <summary>
    /// model�̃��[�h�ƃ^�O�t��
    /// </summary>
    /// <returns></returns>
    SkyDome();
    //model�̃f���[�g
    ~SkyDome();
    /// <summary>
    /// model�̕`��
    /// </summary>
    void Draw();

private:
    int modelHandle;
};

