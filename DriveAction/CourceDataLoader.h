#pragma once
#include <string>
#include<list>
#include "VECTOR3Loader.h"
#include "DxLib.h"
/// <summary>
/// �R�[�X���̕ۊǌ�
/// </summary>
class CourceDataLoader
{
public:
    /// <summary>
    /// �R�[�X���
    /// </summary>
    CourceDataLoader();
    //�f�X�g���N�^
    ~CourceDataLoader();
    /// <summary>
    /// �R�[�X�̃~�j�}�b�v
    /// </summary>
    /// <returns></returns>
    static const std::string GetStageDataGenericAddress();
    static std::list<VECTOR> GetVECTORData(std::string address);
private:
    //�f�[�^�̒u���ꏊ
    const std::string prevAddress = "data/stageData/";
    //���ʂ̃A�h���X
    static std::string genericAddress;
};