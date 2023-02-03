#pragma once
#include "Object.h"
#include "DxLib.h"
/// <summary>
/// ������
/// </summary>
class AccelerationFloor :
    public Object
{
public:
    AccelerationFloor();
    /// <summary>
    /// �������̏ꏊ�ƕ���
    /// </summary>
    /// <param name="pos"></param>
    /// <param name="angularY"></param>
    AccelerationFloor(VECTOR pos, VECTOR angularY);
    ~AccelerationFloor();
    /// <summary>
    /// �X�V
    /// </summary>
    void Update();
    /// <summary>
    /// �`��
    /// </summary>
    void Draw();
private:
    // �����x
    const float addAccel = 50.0f;
    //�@���a
    const float setRadius = 27.0f;
    //�傫��
    const float setScale = 5.0f;
    //�G�t�F�N�g�@�i�{�́j
    int effekseerModelHandle;
    //
    int playingEffect;
};