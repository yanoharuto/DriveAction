#pragma once
/// <summary>
/// ���ӂ̏�
/// </summary>
enum class NeighborhoodSituation
{
    cource,//���ʂɑ����R�[�X
    outside,//�R�[�X�̊O��
    player,//�v���C���[������
    obstacle//��Q��������
};
/// <summary>
/// ���ӏ��@
/// </summary>
struct NeighborhoodInfo
{
    //�e�����ɉ������邩������
    NeighborhoodSituation diagonallyForwardRight, forward, diagonallyForwardLeft;
}; 
