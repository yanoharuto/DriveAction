#pragma once
#include "UIDataStruct.h"
#include <string>
/// <summary>
/// UI
/// </summary>
class UI abstract
{
public:
    UI() { uiData = {}; };
    /// <summary>
    /// �ǂ̈ʒu�ɕ`�悷�邩�Ƃ��`�悵�������̂Ƃ��n���ė~����
    /// </summary>
    /// <param name="data"></param>
    UI(UIData data) { uiData = data; };
    virtual ~UI() {};
    /// <summary>
    /// �`��
    /// </summary>
    virtual void DrawUI() {};
    /// <summary>
    /// �ʒu�ύX
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    void SetXY(int x, int y) { uiData.x = x; uiData.y = y; };
protected:
    //�`��ꏊ�ƕ`��Ώۂ̃f�[�^
    UIData uiData;
};