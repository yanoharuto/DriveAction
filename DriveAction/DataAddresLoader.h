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
    DataAddressLoader(std::string fileName);
    ~DataAddressLoader();
    std::list<std::string>::iterator GetBeginIterator();
    std::list<std::string>::iterator GetEndIterator();
private:
    /// <summary>
    /// 
    /// </summary>
    /// <param name="stringList">�����Ƀf�[�^�̃A�h���X������</param>
    /// <param name="fileName"></param>
    void LoadAddres(std::string fileName);
    std::list<std::string> stringList;
};