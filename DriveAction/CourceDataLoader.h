#pragma once
#include <string>
#include<list>
#include "VECTOR3Loader.h"
#include "DxLib.h"
/// <summary>
/// コース情報の保管庫
/// </summary>
class CourceDataLoader
{
public:
    /// <summary>
    /// コース情報
    /// </summary>
    CourceDataLoader();
    //デストラクタ
    ~CourceDataLoader();
    /// <summary>
    /// コースのミニマップ
    /// </summary>
    /// <returns></returns>
    const std::string GetMiniMapImgAddress();
    /// <summary>
    /// コースの外側のアドレス
    /// </summary>
    /// <returns></returns>
    const std::string GetOutsideAddress();
    /// <summary>
    /// コースのmodelのアドレス
    /// </summary>
    /// <returns></returns>
    const std::string GetCourceAddress();
    
    /// <summary>
    /// 車の初期位置
    /// </summary>
    /// <returns></returns>
    const std::list<VECTOR> GetCarFirstPosList();
    /// <summary>
    /// 車の初期方向
    /// </summary>
    /// <returns></returns>
    const VECTOR GetCarFirstDir();
    /// <summary>
    /// チェックポイントの位置リスト
    /// </summary>
    /// <returns></returns>
    const std::list<VECTOR> GetCheckPointPosList();
    /// <summary>
    /// チェックポイントの方向リスト
    /// </summary>
    /// <returns></returns>
    const std::list<VECTOR> GetCheckPointDirList();
    /// <summary>
    /// 加速床の位置リスト
    /// </summary>
    /// <returns></returns>
    const std::list<VECTOR> GetAccelFloorPosList();
    /// <summary>
    /// 加速床の向きリスト
    /// </summary>
    /// <returns></returns>
    const std::list<VECTOR> GetAccelFloorDirList();
    /// <summary>
    /// 障害物の位置リスト
    /// </summary>
    /// <returns></returns>
    const std::list<VECTOR> GetObstraclePosList();
    /// <summary>
    /// アイテムの配置場所リスト
    /// </summary>
    /// <returns></returns>
    const std::list<VECTOR> GetItemPosList();
    /// <summary>
    /// アイテムの置き方の指標
    /// </summary>
    /// <returns></returns>
    const std::list<VECTOR> GetItemDirList();
private:
    //データの置き場所
    const std::string prevAddress = "data/stageData/";
    //初期位置が書いてあるテキスト
    const std::string firstPosAddress = "/firstPosition.txt";
    //ゴールまでの道のりテキスト
    const std::string checkPointPosAddress = "/CourcePos.txt";        // ;"/checkPointPos.txt"
    //ゴールまでの道のりテキスト
    const std::string checkPointDirAddress = "/CourceDir.txt";         //;"/checkPointDir.txt"
    //コースのモデル
    const std::string courceAddress = "/Asset/RaceCircuit.mv1";
    //コースの外側のモデル
    const std::string outsideAddress = "/Asset/CircuitOutside.mv1";
    //ミニマップの画像のアドレス
    const std::string miniMapAddress = "/Asset/CircuitMap.png";
    //加速床の位置リストのアドレス
    const std::string accelerationFloorPosAddress="/accelFloorPos.txt";
    //加速床の方向リストのアドレス
    const std::string accelerationFloorDirAddress="/accelFloorDir.txt";
    //お邪魔の位置リストのアドレス
    const std::string obstaclePosListAddress = "/obstraclePos.txt";

    //アイテムボックスが並ぶ方向のリスト　外積で左右を取る
    const std::string itemBoxDirAddress = "/ItemDir.txt";
    //アイテムボックスの場所
    const std::string itemBoxPosAddress = "/ItemPos.txt";
    //共通のアドレス
    std::string genericAddress;
    //車の初期位置リストを読み取る
    VECTOR3Loader* firstCarPosLoader;
    //チェックポイントの位置リストを読み取る
    VECTOR3Loader* checkPointPosLoader;
    //チェックポイントの方向リストを読み取る
    VECTOR3Loader* checkPointDirLoader;
    //加速床の位置リストを読み取る
    VECTOR3Loader* accelFloorPosLoader;
    //加速床の向きリストを読み取る
    VECTOR3Loader* accelFloorDirLoader;
    //障害物の位置リストを読み取る
    VECTOR3Loader* obstraclePosLoader;
    VECTOR3Loader* itemDirLoader;
    VECTOR3Loader* itemPosLoader;
};