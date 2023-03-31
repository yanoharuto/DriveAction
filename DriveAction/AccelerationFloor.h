#pragma once
#include "Actor.h"
#include "DxLib.h"
/// <summary>
/// ������
/// </summary>
class AccelerationFloor :
    public Actor
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
    void Update() override;
    /// <summary>
    /// �`��
    /// </summary>
    void Draw() override;
private:
    // �����x
    const float addAccel = 50.0f;
    //�@���a
    const float setRadius = 27.0f;
    //�傫��
    const float setScale = 5.0f;
    //�G�t�F�N�g�@�i�{�́j
    int effekseerModelHandle;
    //d
    int playingEffect;
};