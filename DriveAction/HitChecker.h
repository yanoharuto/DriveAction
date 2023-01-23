#pragma once
struct ConflictExamineResultInfo;
class Object;
/// <summary>
/// �����m�̓����蔻������܂�
/// </summary>
class HitChecker
{
public:
    HitChecker();
    ~HitChecker();
    /// <summary>
    /// �����������ǂ������ׂ��
    /// </summary>
    /// <param name="objA">���ׂ����I�u�W�F�N�gA<</param>
    /// <param name="objB">���ׂ����I�u�W�F�N�gB</param>
    /// <returns>����������True</returns>
    bool HitCheck(Object* const objA, Object* const objB);
    /// <summary>
    /// �����������ǂ������ׂ��
    /// </summary>
    /// <param name="objA">���ׂ����I�u�W�F�N�gA<</param>
    /// <param name="objBInfo">���ׂ����I�u�W�F�N�gB</param>
    /// <returns>����������True</returns>
    bool HitCheck(Object* const objA, const ConflictExamineResultInfo objBInfo);
    /// <summary>
    /// �����������ǂ������ׂ��
    /// </summary>
    /// <param name="objAInfo">���ׂ����I�u�W�F�N�gA<</param>
    /// <param name="objBInfo">���ׂ����I�u�W�F�N�gB</param>
    /// <returns>����������True</returns>
    bool HitCheck(const ConflictExamineResultInfo objAInfo, const ConflictExamineResultInfo objBInfo);
private:
    /// <summary>
    /// �����������ǂ������ׂ�Ƃ��̋��ʏ���
    /// </summary>
    /// <param name="objAInfo">���ׂ����I�u�W�F�N�gA</param>
    /// <param name="objBInfo">���ׂ����I�u�W�F�N�gB</param>
    /// <returns>����������True</returns>
    bool HitCheckProcess(ConflictExamineResultInfo objAInfo, ConflictExamineResultInfo objBInfo);
};

