#pragma once
#include <list>
#include "DxLib.h"
struct CircuitData
{
    //�Ԃ����ɍs���ׂ��s���悪�����Ă���
    std::list<VECTOR> positionVec;
    //�t�����ăS�[�����Ȃ��悤�ɕ������悹��
    std::list<VECTOR> directionVec;
};