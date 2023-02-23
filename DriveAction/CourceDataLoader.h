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
    /// <summary>
    /// �Ԃ̏����ʒu
    /// </summary>
    /// <returns></returns>
    static const std::list<VECTOR> GetCarFirstPosList();
    /// <summary>
    /// �`�F�b�N�|�C���g�̈ʒu���X�g
    /// </summary>
    /// <returns></returns>
    static const std::list<VECTOR> GetCheckPointPosList();
    /// <summary>
    /// �`�F�b�N�|�C���g�̕������X�g
    /// </summary>
    /// <returns></returns>
    static const std::list<VECTOR> GetCheckPointDirList();
    /// <summary>
    /// �������̈ʒu���X�g
    /// </summary>
    /// <returns></returns>
    static const std::list<VECTOR> GetAccelFloorPosList();
    /// <summary>
    /// �������̌������X�g
    /// </summary>
    /// <returns></returns>
    static const std::list<VECTOR> GetAccelFloorDirList();
    /// <summary>
    /// ��Q���̈ʒu���X�g
    /// </summary>
    /// <returns></returns>
    static const std::list<VECTOR> GetObstraclePosList();
    /// <summary>
    /// �A�C�e���̔z�u�ꏊ���X�g
    /// </summary>
    /// <returns></returns>
    static const std::list<VECTOR> GetItemPosList();
    /// <summary>
    /// �A�C�e������񂸂u�����߂̓z
    /// </summary>
    /// <returns></returns>
    static const std::list<VECTOR> GetItemDirList();
private:
    //�f�[�^�̒u���ꏊ
    const std::string prevAddress = "data/stageData/";
    //�����ʒu�������Ă���e�L�X�g
    const std::string firstPosAddress = "/firstPosition.txt";
    //�S�[���܂ł̓��̂�e�L�X�g
    const std::string checkPointPosAddress = "/CourcePos.txt";        
    //�S�[���܂ł̓��̂�e�L�X�g
    const std::string checkPointDirAddress = "/CourceDir.txt";        
    //�������̈ʒu���X�g�̃A�h���X
    const std::string accelerationFloorPosAddress="/accelFloorPos.txt";
    //�������̕������X�g�̃A�h���X
    const std::string accelerationFloorDirAddress="/accelFloorDir.txt";
    //���ז��̈ʒu���X�g�̃A�h���X
    const std::string obstaclePosListAddress = "/obstraclePos.txt";
    //�A�C�e���{�b�N�X�����ԕ����̃��X�g�@�O�ςō��E�����
    const std::string itemBoxDirAddress = "/ItemDir.txt";
    //�A�C�e���{�b�N�X�̏ꏊ
    const std::string itemBoxPosAddress = "/ItemPos.txt";
};