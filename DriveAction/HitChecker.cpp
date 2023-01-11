#include "HitChecker.h"
#include "Object.h"
#include "ArgumentObjInfoStruct.h"
#include "DxLib.h"
HitChecker::HitChecker()
{
}

HitChecker::~HitChecker()
{
}
/// <summary>
/// �����������ǂ������ׂ��
/// </summary>
/// <param name="objA">���ׂ����I�u�W�F�N�gA</param>
/// <param name="objB">���ׂ����I�u�W�F�N�gB</param>
/// <returns>����������True</returns>
bool HitChecker::HitCheck(Object* const objA, Object* const objB)
{
    ArgumentConflictInfo aInfo;
    aInfo.SetObjInfo(false, objA);
    ArgumentConflictInfo bInfo;
    bInfo.SetObjInfo(false,objB);
    return HitCheckProcess(aInfo, bInfo);
}
/// <summary>
/// �����������ǂ������ׂ��
/// </summary>
/// <param name="objA">���ׂ����I�u�W�F�N�gA</param>
/// <param name="objBInfo">���ׂ����I�u�W�F�N�gB</param>
/// <returns>����������True</returns>
bool HitChecker::HitCheck(Object* const objA, const ArgumentConflictInfo objBInfo)
{
    ArgumentConflictInfo aInfo;
    aInfo.SetObjInfo(false,objA);
    return HitCheckProcess(aInfo, objBInfo);
}
/// <summary>
/// �����������ǂ������ׂ��
/// </summary>
/// <param name="objAInfo">���ׂ����I�u�W�F�N�gA</param>
/// <param name="objBInfo">���ׂ����I�u�W�F�N�gB</param>
/// <returns>����������True</returns>
bool HitChecker::HitCheck(const ArgumentConflictInfo objAInfo, const ArgumentConflictInfo objBInfo)
{
    return HitCheckProcess(objAInfo, objBInfo);
}
/// <summary>
/// �����������ǂ������ׂ�Ƃ��̋��ʏ���
/// </summary>
/// <param name="objAInfo">���ׂ����I�u�W�F�N�gA</param>
/// <param name="objBInfo">���ׂ����I�u�W�F�N�gB</param>
/// <returns>����������True</returns>
bool HitChecker::HitCheckProcess(ArgumentConflictInfo objAInfo, ArgumentConflictInfo objBInfo)
{
    //�������m�̋���
    VECTOR distance = VSub(objAInfo.pos, objBInfo.pos);
    distance.y = 0;
    //�������m�̓����蔻��̍��v
    float range = objAInfo.radius + objBInfo.radius;
    if (range > VSize(distance))
    {
        return true;
    }
    return false;
}