#pragma once
#include "DataAddresLoader.h"
#include <list>
#include <string>

/// <summary>
/// �^�C�g����ʂŃX�e�[�W�I�Ԏ��Ɏg��
/// </summary>
class StageSelect
{
public:
    /// <summary>
    /// �X�e�[�W���ƂɕK�v�ȃA�Z�b�g�̃A�h���X��
    /// �����Ă���t�@�C����
    /// �A�h���X�������Ă���t�@�C����ǂݍ���
    /// </summary>
    /// <returns></returns>
    StageSelect();
    ~StageSelect();
    /// <summary>
    /// �V�ԃX�e�[�W�ύX����Ƃ��Ɏg��
    /// </summary>
    /// <param name="next">���̃X�e�[�WTrue�O�̃X�e�[�W��false</param>
    void ChangeStage(bool next);
    /// <summary>
    /// �ǂ̃X�e�[�W��I��ł��邩
    /// </summary>
    /// <returns></returns>
    static std::string GetLoadeStageName();
private:
    std::list<std::string>::iterator fileNameIte;//�v���C���[���V�т����X�e�[�W�̃A�Z�b�g�̃A�h���X���w��
    const std::string allStageAddresFile = "data/stageData/AllStageFileName.txt";//�X�e�[�W�̈ꗗ�I�ȓz
    DataPassLoader* dataLoader;
};

