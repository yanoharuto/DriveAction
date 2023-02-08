#pragma once
#include <string>
#include <fstream>
#include "DxLib.h"
/// <summary>
/// ベクターのデータをメモ帳に記録する
/// </summary>
class VectorDataCreator
{
public:
    VectorDataCreator();
    /// <summary>
    /// 開くメモ帳のファイルネーム
    /// </summary>
    /// <param name="setFileName"></param>
    VectorDataCreator(std::string setFileName);
    ~VectorDataCreator();
    /// <summary>
    /// 追加で書き込む
    /// </summary>
    /// <param name="vec"></param>
    void WriteVECTOR(VECTOR vec);
private:
    std::ofstream writing_file;
    std::string fileName;
};

