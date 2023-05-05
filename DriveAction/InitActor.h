#pragma once
#include <vector>
#include <string>
#include "InitObjKind.h"

//����������p�����[�^�[
enum InitObjParamator;
struct ActorParametor;
/// <summary>
/// actor�̏�����������
/// </summary>
class InitActor
{
public:
    InitActor();
    ~InitActor();
    
    ActorParametor GetActorParametor(Init::InitObjKind obj);
private:
    std::vector<std::string> initDataPassFile;
    std::string initActorFileName = "data/model/InitObjPass.csv";
};

/// <summary>
/// ����������v�f
/// </summary>
enum InitObjParamator
{
    //model�̑��΃p�X
    assetPass = 2,
    //�傫��
    modelSize = 5,
    //�ŏ��̃|�W�V����
    firstPosY = 8,
    //model�̓����蔼�a
    collRadius = 11,
    //���˕Ԃ�̑傫��
    bouncePower = 14,
    //�\����
    compositionNum = 17
};
/// <summary>
/// �������̍ۂɎg��
/// </summary>
struct ActorParametor
{
    float firstPosY;
    float setModelSize;
    float setRadius;
    float setBouncePow;
    std::string modelPass;

};