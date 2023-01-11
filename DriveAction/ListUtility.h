#pragma once
#include <list>
#include "DxLib.h"
/// <summary>
/// 第二引数分回したイテレーターのVECTORを返す
/// </summary>
/// <param name="listIte">回したいイテレーター</param>
/// <param name="count">イテレーターを回したい回数</param>
/// <returns></returns>
VECTOR GetArgumentCountVector(std::list<VECTOR>::iterator listIte, int count)
{
    for (int i = 0; i < count; i++)
    {
        listIte++;
    }
    return *listIte;
}