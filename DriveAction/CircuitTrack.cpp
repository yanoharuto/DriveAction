#include "CircuitTrack.h"
#include "Player.h"
/// <summary>
/// ������
/// </summary>
/// <param name="player">�v���C���[�̕������</param>
/// <returns></returns>
CircuitTrack::CircuitTrack(Player* player)
{
    courceModelHandle = MV1LoadModel("data/model/Circuit/CircuitCource.mv1");
    outsideModelHandle = MV1LoadModel("data/model/Circuit/CircuitOutside.mv1");
    //�኱�R�[�X�̊O����������
    MV1SetPosition(outsideModelHandle, outsideModelPosition);

    VECTOR scale = VGet(courceModeScaleValue, courceModeScaleValue, courceModeScaleValue);
    MV1SetScale(courceModelHandle, scale);
    scale = VGet(outsideModelScaleValue, outsideModelScaleValue, outsideModelScaleValue);
    MV1SetScale(outsideModelHandle, scale);

    tag = ObjectTag::stage;
    int playerRadius = static_cast<int>(player->GetRadius());
    playerRadius *= playerRadius;
    //�R���W���������
    MV1SetupCollInfo(outsideModelHandle, -1,playerRadius, setupYDivNum ,playerRadius,-1);
}
/// <summary>
/// model�̉���@�R���W������������
/// </summary>
/// <returns></returns>
CircuitTrack::~CircuitTrack()
{
    MV1DeleteModel(courceModelHandle);
    MV1DeleteModel(outsideModelHandle);
}
/// <summary>
/// �R�[�X�̊O���ɓ������Ă邩���ׂ�
/// </summary>
/// <param name="actor">�O���ɂ��邩���ׂ�������</param>
/// <returns>�R�[�X�̊O���ɂ���Ȃ�True</returns>
bool CircuitTrack::GetOutsideHitFlag(Actor* actor)
{
    //�����̎n�܂�ƏI�������
    //���Ƃ����W������Ă���
    VECTOR startPos = actor->GetPos();
    startPos.y = sY;
    VECTOR endPos = startPos;
    endPos.y = eY;
    //�O���ɂ��邩���ׂ�
    DxLib::MV1_COLL_RESULT_POLY polyInfo = MV1CollCheck_Line(outsideModelHandle, -1, startPos, endPos);
    return polyInfo.HitFlag;
}

/// <summary>
/// �R�[�X�̃��f����`��
/// </summary>
void CircuitTrack::Draw()
{
    MV1DrawModel(courceModelHandle);
    MV1DrawModel(outsideModelHandle);
}
