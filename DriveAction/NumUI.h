#pragma once
#include <string>
#include "UIManager.h"

#define TIMER_FONT_NUM 10
/// <summary>
/// ������`�悷��
/// </summary>
class NumUI
{
public:
    NumUI();
    ~NumUI();
    /// <summary>
    /// ������`�悵�������p
    /// </summary>
    /// <param name="x">��ԉE�[</param>
    /// <param name="y">Y���W</param>
    /// <param name="num">����</param>
    /// <param name="scale">�����̑傫��</param>
    /// <returns>���[�̍��W</returns>
    int Draw(int x, int y, int num,float scale);
    /// <summary>
    /// �����_���`�悵�������p
    /// </summary>
    /// <param name="x">��ԉE�[</param>
    /// <param name="y">Y���W</param>
    /// <param name="num">����</param>
    /// <param name="scale">�����̑傫��</param>
    /// <returns>���[�̍��W</returns>
    int Draw(int x, int y, float num,float scale);
    /// <summary>
    /// �ꕶ���̑傫��
    /// </summary>
    /// <returns></returns>
    int GetNumWidthSize();
private:
    //�����̃f�[�^
    UIData numData;
    //�����_�̉摜
    UIData pointData;
};