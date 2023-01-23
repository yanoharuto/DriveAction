#include "CourceDataLoader.h"
#include "Utility.h"
#include "StageSelect.h"
#include <iostream>
#include <fstream>
#include <string>
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
}
CourceDataLoader::~CourceDataLoader()
{
    SAFE_DELETE(firstCarPosLoader);
    SAFE_DELETE(checkPointDirLoader);
    SAFE_DELETE(checkPointPosLoader);
    SAFE_DELETE(accelFloorPosLoader);
    SAFE_DELETE(accelFloorDirLoader);
    SAFE_DELETE(obstraclePosLoader);
}
/// <summary>
/// �R�[�X�̃~�j�}�b�v
/// </summary>
/// <returns></returns>
const std::string CourceDataLoader::GetMiniMapImgAddress()
{
    std::string chara = genericAddress + miniMapAddress;
    return chara;
}
/// <summary>
/// �R�[�X�̊O���̃A�h���X
/// </summary>
/// <returns></returns>
const std::string CourceDataLoader::GetOutsideAddress()
{
    std::string chara = genericAddress + outsideAddress;
    return chara;
}
/// <summary>
/// �R�[�X��model�̃A�h���X
/// </summary>
/// <returns></returns>
const std::string CourceDataLoader::GetCourceAddress()
{
    std::string chara = genericAddress + courceAddress;
    return chara;
}
/// <summary>
/// ��Q���̃A�h���X
/// </summary>
/// <returns></returns>
const std::string CourceDataLoader::GetObstracleAddress()
{
    std::string chara = prevAddress + obstacleModelAddress;
    return chara;
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
/// �Ԃ̏�������
/// </summary>
/// <returns></returns>
const VECTOR CourceDataLoader::GetCarFirstDir()
{
    return *firstCarPosLoader->GetVectorList().begin();
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
