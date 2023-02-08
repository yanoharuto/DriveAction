#pragma once
#include <string>
#include "VectorDataCreator.h"
#include "DxLib.h"
/// <summary>
/// コースのデータを作るのに使う
/// </summary>
class CreatePosAndDirData
{
public:
    CreatePosAndDirData();
    ~CreatePosAndDirData();
    /// <summary>
    /// 曲がる時だけコースデータを記録する
    /// </summary>
    /// <param name="pos"></param>
    /// <param name="dir"></param>
    void WriteWhereToTurn(VECTOR pos,VECTOR dir);
    /// <summary>
    /// コースデータを記録する
    /// </summary>
    /// <param name="pos"></param>
    /// <param name="dir"></param>
    void WritePosAndDir(VECTOR pos,VECTOR dir);
private:
    //コースを通る時の方向
    std::string dirFileName = "CourceDir.txt";
    //コースを通る時の場所
    std::string posFileName = "CourcePos.txt";
    //方向記録係
    VectorDataCreator* dirDataCreator;
    //場所記録係
    VectorDataCreator* posDataCreator;
    //最後に曲がった時の方向
    VECTOR prevVec = {-0.999753,0.00000,-0.022217};
    //曲がった判定で使う
    const float turnProccesLine = 3.0f;
};

