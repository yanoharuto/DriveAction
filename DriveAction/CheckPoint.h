#pragma once
#include "Car.h"
#include <vector>
struct CircuitData
{
    //�Ԃ����ɍs���ׂ��s���悪�����Ă���
    std::vector<VECTOR> positionVec;
    //�t�����ăS�[�����Ȃ��悤�ɕ������悹��
    std::vector<VECTOR> directionVec;
    //���T������S�[���Ȃ̂�
    int goalRoundNum = 0;
};
/// <summary>
/// �v���C���[������S�[��������������
/// </summary>
class CheckPoint final:
    public Object
{
public:
    CheckPoint();
    /// <summary>
   /// �R�[�X��񓾂����
   /// </summary>
   /// <param name="roundNum">���T���邩</param>
   /// <param name="fileName">�ǂ̃t�@�C�����珊�����邩</param>
   /// <returns></returns>
    CheckPoint(const int roundNum,const TCHAR* fileName);
    /// <summary>
    /// �R�[�X��񕡐��p
    /// </summary>
    /// <param name="checkPointParam"></param>
    /// <returns></returns>
    CheckPoint(const CircuitData circuitData);
    //�f�X�g���N�^
    ~CheckPoint();
    /// <summary>
    /// �v���C���[���Ԃ������玟�̍s�����ݒ肷��
    /// </summary>
    /// <param name="car"></param>
    void Update(Car* car);
    /// <summary>
    /// ����CPU�ɂ��R�s�[�����邽�߂ɓn��
    /// </summary>
    /// <returns></returns>
    CircuitData GetCheckPoint() const;
private:
    /// <summary>
    /// ����������
    /// </summary>
    void InitMember();
    CircuitData cPParam;
    //position���炱�ꂾ���߂�������S�[��
    const float goalRadius = 80.0f;
    //�Ԃ�Dir�Ɣ��Ό����Ȃ̂œ��ς������1�ɋ߂�������S�[����������
    const float dirJugeLine = 0.8f;
    //�S�[�����ꂽ��
    int goalNum = 0;
    //�x�N�^�[�z��̃T�C�Y
    int vecSize = 0;

};

