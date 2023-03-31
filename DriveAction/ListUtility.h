#pragma once
#include <list>
#include <vector>
#include "DxLib.h"

/// <summary>
/// ���������񂵂��C�e���[�^�[��VECTOR��Ԃ�
/// </summary>
/// <param name="listIte">�񂵂����C�e���[�^�[</param>
/// <param name="count">�C�e���[�^�[���񂵂�����</param>
/// <returns></returns>
template<typename T>
T GetIncrementList(std::list<T> list, int count)
{
    auto ite = list.begin();
    for (int i = 0; i < count; i++)
    {
        ite++;
    }
    return *ite;
}

/// <summary>
/// ���X�g��VECTOR�ɕϊ�����
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="list"></param>
/// <returns></returns>
template<typename T>
std::vector<T> GetVectorConversion(std::list<T> list)
{
    std::vector<T> tempPos(list.begin(), list.end());
    return tempPos;
}
