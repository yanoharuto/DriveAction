#pragma once
#include "DataAddresLoader.h"
#include <list>
#include <string>

/// <summary>
/// タイトル画面でステージ選ぶ時に使う
/// </summary>
class StageSelect
{
public:
    /// <summary>
    /// ステージごとに必要なアセットのアドレスが
    /// 書いてあるファイルの
    /// アドレスが書いてあるファイルを読み込む
    /// </summary>
    /// <returns></returns>
    StageSelect();
    ~StageSelect();
    /// <summary>
    /// 遊ぶステージ変更するときに使う
    /// </summary>
    /// <param name="next">次のステージTrue前のステージかfalse</param>
    void ChangeStage(bool next);
    /// <summary>
    /// どのステージを選んでいるか
    /// </summary>
    /// <returns></returns>
    static std::string GetLoadeStageName();
private:
    std::list<std::string>::iterator fileNameIte;//プレイヤーが遊びたいステージのアセットのアドレスを指す
    const std::string allStageAddresFile = "data/stageData/AllStageFileName.txt";//ステージの一覧的な奴
    DataPassLoader* dataLoader;
};

