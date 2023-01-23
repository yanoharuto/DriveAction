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
    const std::string GetMiniMapImgAddress();
    /// <summary>
    /// �R�[�X�̊O���̃A�h���X
    /// </summary>
    /// <returns></returns>
    const std::string GetOutsideAddress();
    /// <summary>
    /// �R�[�X��model�̃A�h���X
    /// </summary>
    /// <returns></returns>
    const std::string GetCourceAddress();
    /// <summary>
    /// ��Q���̃A�h���X
    /// </summary>
    /// <returns></returns>
    const std::string GetObstracleAddress();
    /// <summary>
    /// �Ԃ̏����ʒu
    /// </summary>
    /// <returns></returns>
    const std::list<VECTOR> GetCarFirstPosList();
    /// <summary>
    /// �Ԃ̏�������
    /// </summary>
    /// <returns></returns>
    const VECTOR GetCarFirstDir();
    /// <summary>
    /// �`�F�b�N�|�C���g�̈ʒu���X�g
    /// </summary>
    /// <returns></returns>
    const std::list<VECTOR> GetCheckPointPosList();
    /// <summary>
    /// �`�F�b�N�|�C���g�̕������X�g
    /// </summary>
    /// <returns></returns>
    const std::list<VECTOR> GetCheckPointDirList();
    /// <summary>
    /// �������̈ʒu���X�g
    /// </summary>
    /// <returns></returns>
    const std::list<VECTOR> GetAccelFloorPosList();
    /// <summary>
    /// �������̌������X�g
    /// </summary>
    /// <returns></returns>
    const std::list<VECTOR> GetAccelFloorDirList();
    /// <summary>
    /// ��Q���̈ʒu���X�g
    /// </summary>
    /// <returns></returns>
    const std::list<VECTOR> GetObstraclePosList();
private:
    //�f�[�^�̒u���ꏊ
    const std::string prevAddress = "data/stageData/";
    //�����ʒu�������Ă���e�L�X�g
    const std::string firstPosAddress = "/firstPosition.txt";
    //�S�[���܂ł̓��̂�e�L�X�g
    const std::string checkPointPosAddress = "/checkPointPos.txt";
    //�S�[���܂ł̓��̂�e�L�X�g
    const std::string checkPointDirAddress = "/checkPointDir.txt";
    //�R�[�X�̃��f��
    const std::string courceAddress = "/Asset/RaceCircuit.mv1";
    //�R�[�X�̊O���̃��f��
    const std::string outsideAddress = "/Asset/CircuitOutside.mv1";
    //�~�j�}�b�v�̉摜�̃A�h���X
    const std::string miniMapAddress = "/Asset/CircuitMap.png";
    //�������̈ʒu���X�g�̃A�h���X
    const std::string accelerationFloorPosAddress="/accelFloorPos.txt";
    //�������̕������X�g�̃A�h���X
    const std::string accelerationFloorDirAddress="/accelFloorDir.txt";
    //���ז��̈ʒu���X�g�̃A�h���X
    const std::string obstaclePosListAddress = "/obstraclePos.txt";
    //���ז���model�̃A�h���X
    const std::string obstacleModelAddress = "/gimmick/Saw.mv1";
    //���ʂ̃A�h���X
    std::string genericAddress;
    //�Ԃ̏����ʒu���X�g��ǂݎ��
    VECTOR3Loader* firstCarPosLoader;
    //�`�F�b�N�|�C���g�̈ʒu���X�g��ǂݎ��
    VECTOR3Loader* checkPointPosLoader;
    //�`�F�b�N�|�C���g�̕������X�g��ǂݎ��
    VECTOR3Loader* checkPointDirLoader;
    //�������̈ʒu���X�g��ǂݎ��
    VECTOR3Loader* accelFloorPosLoader;
    //�������̌������X�g��ǂݎ��
    VECTOR3Loader* accelFloorDirLoader;
    //��Q���̈ʒu���X�g��ǂݎ��
    VECTOR3Loader* obstraclePosLoader;
};