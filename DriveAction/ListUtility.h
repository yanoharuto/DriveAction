#pragma once
#include <list>
#include <vector>
#include "DxLib.h"

/// <summary>
/// 第二引数分回したイテレーターのVECTORを返す
/// </summary>
/// <param name="listIte">回したいイテレーター</param>
/// <param name="count">イテレーターを回したい回数</param>
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
/// リストをVECTORに変換する
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
