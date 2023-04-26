#pragma once
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include "DxLib.h"

/// <summary>
/// ���������񂵂��C�e���[�^�[��VECTOR��Ԃ�
/// </summary>
/// <param name="listIte">�񂵂����C�e���[�^�[</param>
/// <param name="count">�C�e���[�^�[���񂵂�����</param>
/// <returns></returns>
template<typename T>
static T GetIncrementList(std::list<T> list, int count)
{
    auto ite = list.begin();
    for (int i = 0; i < count; i++)
    {
        ite++;
    }
    return *ite;
}

/// <summary>
/// ���X�g���x�N�^�[
/// �ɕϊ�����
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="list"></param>
/// <returns></returns>
template<typename T>
static std::vector<T> ConvertListToVector(std::list<T> list)
{
    std::vector<T> newList(list.begin(), list.end());
    return newList;
}
/// <summary>
/// �x�N�^�[���烊�X�g�ɂ���
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="vector"></param>
/// <returns></returns>
template<typename T>
static std::list<T> ConvertVectorToList(std::vector<T> vector)
{
    std::list<T> newVec(vector.begin(), vector.end());
    return newVec;
}

static std::list<std::string>LoadData(std::string fileName)
{
    std::ifstream ifs(fileName);
    if (!ifs)
    {
        std::cerr << "�ǂݍ��݂Ɏ��s" << std::endl;
        std::exit(1);
    }
    std::string charBuf;
    std::list<std::string> stringList;
    for (int i = 0; std::getline(ifs, charBuf); i++)
    {
        std::string backspaceChar = charBuf;
        stringList.push_back(backspaceChar);
    }
    return stringList;
}