#pragma once
#include "Stage.h"
class Player;
/// <summary>
/// �R�[�X
/// </summary>
class CircuitTrack final:
    public Stage
{
public:
    /// <summary>
    /// ������
    /// </summary>
    /// <returns></returns>
    CircuitTrack(Player* player);
    
    ///model���f���[�g
    ~CircuitTrack();
    /// <summary>
    /// �X�e�[�W�̂ǂ�material�̏�ɂ��邩���ׂ�
    /// </summary>
    /// <param name="object"></param>
    void ConflictProcess(Actor* actor)override;
    /// <summary>
    /// �R�[�X�̃��f����`��
    /// </summary>
    void Draw();

private:
    float const scaleValue = 0.15f;
    int modelHandle;
    int materialNum;
    float sY = 0.5;
    float eY = -1.2;
};

