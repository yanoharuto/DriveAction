#pragma once
#include <list>
#include <string>
/// <summary>
///　データのアドレスとかを読み取る
/// </summary>
class DataAddressLoader
{
public:
    DataAddressLoader();
    ~DataAddressLoader();
    /// <summary>
    /// 
    /// </summary>
    /// <param name="stringList">ここにデータのアドレスを入れる</param>
    /// <param name="fileName"></param>
    void GetString(std::list <std::string>* stringList, std::string fileName);
};