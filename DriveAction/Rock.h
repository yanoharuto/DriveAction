#pragma once
#include "SphereCollider.h"
#include "Actor.h"
//��̃p�^�[���@�傫���Ƃ����ς��
#define RockPattern 3
/// <summary>
/// ��
/// </summary>
class Rock :
    public Actor
{
public:
    /// <summary>
    /// ��@3�p�^�[���̊₪����
    /// </summary>
    /// <param name="setPos"></param>
    /// <param name="pattern"></param>
    Rock(VECTOR setPos,int pattern);
    /// <summary>
    /// �����蔻�������
    /// </summary>
    ~Rock();
private:
    //model�̃p�X
    static const std::string modelPass[RockPattern];
    //�Ԃ��������ɕt����΂���
    static const int setBouncePower;
    //�����蔻��̕�
    static const float setRadius[RockPattern]; 
    //�傫��
    VECTOR scale;
    //�������蔻��
    SphereCollider* collider;
};

