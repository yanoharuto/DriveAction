#pragma once
#include <list>
#include <string>
/// <summary>
///�@�f�[�^�̃A�h���X�Ƃ���ǂݎ��
/// </summary>
class DataAddressLoader
{
public:
    DataAddressLoader();
    ~DataAddressLoader();
    /// <summary>
    /// 
    /// </summary>
    /// <param name="stringList">�����Ƀf�[�^�̃A�h���X������</param>
    /// <param name="fileName"></param>
    void GetString(std::list <std::string>* stringList, std::string fileName);
};