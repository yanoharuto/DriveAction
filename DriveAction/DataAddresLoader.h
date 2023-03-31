#pragma once
#include <list>
#include <string>
/// <summary>
///　データのアドレスとかを読み取る
/// </summary>
class DataPassLoader
{
public:
    DataPassLoader();
    DataPassLoader(std::string fileName);
    ~DataPassLoader();
    std::list<std::string>::iterator GetBeginIterator();
    std::list<std::string>::iterator GetEndIterator();
private:
    /// <summary>
    /// 
    /// </summary>
    /// <param name="stringList">ここにデータのアドレスを入れる</param>
    /// <param name="fileName"></param>
    void LoadAddres(std::string fileName);
    std::list<std::string> stringList;
};