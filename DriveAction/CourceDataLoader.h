#pragma once
#include <string>
#include<list>
#include "VECTOR3Loader.h"
#include "DxLib.h"
class CourceDataLoader
{
public:
    CourceDataLoader();
    ~CourceDataLoader();
    const std::string GetMiniMapImgAddress();
    const std::string GetOutsideAddress();
    const std::string GetCourceAddress();
    const std::list<VECTOR> GetFirstPosList();
    const VECTOR GetFirstDir();
    const std::list<VECTOR> GetCheckPointPosList();
    const std::list<VECTOR> GetCheckPointDirList();
private:
    const std::string prevAddress = "data/stageData/";
    const std::string firstPosAddress = "/firstPosition.txt";//�����ʒu�������Ă���e�L�X�g
    const std::string checkPointPosAddress = "/checkPointPos.txt";//�S�[���܂ł̓��̂�e�L�X�g
    const std::string checkPointDirAddress = "/checkPointDir.txt";//�S�[���܂ł̓��̂�e�L�X�g
    const std::string courceAddress = "/Asset/RaceCircuit.mv1";
    const std::string outsideAddress = "/Asset/CircuitOutside.mv1";
    const std::string miniMapAddress = "/Asset/CircuitMap.png";
    VECTOR3Loader* firstPosLoader;
    VECTOR3Loader* checkPointPosLoader;
    VECTOR3Loader* checkPointDirLoader;
};