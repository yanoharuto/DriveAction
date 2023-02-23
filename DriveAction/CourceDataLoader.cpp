#include "CourceDataLoader.h"
#include "Utility.h"
#include "StageSelect.h"
#include <iostream>
#include <fstream>
#include <string>
//���ʂ̃A�h���X
static std::string genericAddress;
//�Ԃ̏����ʒu���X�g��ǂݎ��
static VECTOR3Loader* firstCarPosLoader;
//�`�F�b�N�|�C���g�̈ʒu���X�g��ǂݎ��
static VECTOR3Loader* checkPointPosLoader;
//�`�F�b�N�|�C���g�̕������X�g��ǂݎ��
static VECTOR3Loader* checkPointDirLoader;
//�������̈ʒu���X�g��ǂݎ��
static VECTOR3Loader* accelFloorPosLoader;
//�������̌������X�g��ǂݎ��
static VECTOR3Loader* accelFloorDirLoader;
//��Q���̈ʒu���X�g��ǂݎ��
static VECTOR3Loader* obstraclePosLoader;
static VECTOR3Loader* itemDirLoader;
static VECTOR3Loader* itemPosLoader;
/// <summary>
/// �R�[�X���
/// </summary>
CourceDataLoader::CourceDataLoader()
{
    genericAddress = prevAddress + StageSelect::GetLoadeStageName();
    //�R�[�X��̃I�u�W�F�N�g�̈ʒu�Ƃ������Ƃ�
    firstCarPosLoader = new VECTOR3Loader(genericAddress + firstPosAddress);
    checkPointDirLoader = new VECTOR3Loader(genericAddress + checkPointDirAddress);
    checkPointPosLoader = new VECTOR3Loader(genericAddress + checkPointPosAddress);
    accelFloorDirLoader = new VECTOR3Loader(genericAddress + accelerationFloorDirAddress);
    accelFloorPosLoader = new VECTOR3Loader(genericAddress + accelerationFloorPosAddress);
    obstraclePosLoader = new VECTOR3Loader(genericAddress + obstaclePosListAddress);
    itemDirLoader = new VECTOR3Loader(genericAddress + itemBoxDirAddress);
    itemPosLoader = new VECTOR3Loader(genericAddress + itemBoxPosAddress);
}
CourceDataLoader::~CourceDataLoader()
{
    SAFE_DELETE(firstCarPosLoader);
    SAFE_DELETE(checkPointDirLoader);
    SAFE_DELETE(checkPointPosLoader);
    SAFE_DELETE(accelFloorPosLoader);
    SAFE_DELETE(accelFloorDirLoader);
    SAFE_DELETE(obstraclePosLoader);
    SAFE_DELETE(itemPosLoader);
    SAFE_DELETE(itemDirLoader);
}
/// <summary>
/// �R�[�X�̃~�j�}�b�v
/// </summary>
/// <returns></returns>
const std::string CourceDataLoader::GetStageDataGenericAddress()
{
    return genericAddress;
}

/// <summary>
/// �Ԃ̏����ʒu
/// </summary>
/// <returns></returns>
const std::list<VECTOR> CourceDataLoader::GetCarFirstPosList()
{
    std::list<VECTOR> firstPosList = firstCarPosLoader->GetVectorList();
    return firstPosList;
}
/// <summary>
/// �`�F�b�N�|�C���g�̈ʒu���X�g
/// </summary>
/// <returns></returns>
const std::list<VECTOR> CourceDataLoader::GetCheckPointPosList()
{
    return checkPointPosLoader->GetVectorList();
}
/// <summary>
/// �`�F�b�N�|�C���g�̕������X�g
/// </summary>
/// <returns></returns>
const std::list<VECTOR> CourceDataLoader::GetCheckPointDirList()
{
    return checkPointDirLoader->GetVectorList();
}
/// <summary>
/// �������̈ʒu���X�g
/// </summary>
/// <returns></returns>
const std::list<VECTOR> CourceDataLoader::GetAccelFloorPosList()
{
    return accelFloorPosLoader->GetVectorList();
}
/// <summary>
/// �������̌������X�g
/// </summary>
/// <returns></returns>
const std::list<VECTOR> CourceDataLoader::GetAccelFloorDirList()
{
    return accelFloorDirLoader->GetVectorList();
}
/// <summary>
/// ��Q���̈ʒu���X�g
/// </summary>
/// <returns></returns>
const std::list<VECTOR> CourceDataLoader::GetObstraclePosList()
{
    return obstraclePosLoader->GetVectorList();
}

const std::list<VECTOR> CourceDataLoader::GetItemPosList()
{
    return itemPosLoader->GetVectorList();
}

const std::list<VECTOR> CourceDataLoader::GetItemDirList()
{
    return itemDirLoader->GetVectorList();
}
