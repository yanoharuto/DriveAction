#pragma once
#include <list>
#include "DxLib.h"
/// <summary>
/// ���������񂵂��C�e���[�^�[��VECTOR��Ԃ�
/// </summary>
/// <param name="listIte">�񂵂����C�e���[�^�[</param>
/// <param name="count">�C�e���[�^�[���񂵂�����</param>
/// <returns></returns>
VECTOR GetArgumentCountVector(std::list<VECTOR>::iterator listIte, int count)
{
    for (int i = 0; i < count; i++)
    {
        listIte++;
    }
    return *listIte;
}