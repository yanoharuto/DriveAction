#pragma once
#include <vector>
#include <string>
#include <unordered_map>
enum UIKind;
struct InitUIData;
struct UIData;
/// <summary>
/// UIを纏めるマネージャー
/// </summary>
class UIManager
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <returns></returns>
    UIManager();
    ~UIManager();
    static UIData CreateUIData(UIKind uiKind);
 private:
    static std::vector<std::string> initDataVec;
    static std::unordered_map<UIKind,int*> loadGraphs;
    const std::string initUIDataPassFile = "data/UI/InitUIPass.csv";
};
enum UIKind
{
    //ゲームの目標
    gamePurose = 0 ,
    //収集物のアイコン
    collectIcon = 1,
    //カウントダウン
    countDown = 2,
    //収集物のスコア表示
    collectScore = 3,
    //ダメージを受けると減少するスコア表示
    damageScore = 4,
    //タイム　やスコアの表字
    num = 5,
    //
    manual = 6,
    point = 7,
    radar = 8,
    slash = 9,
    tilteLogo = 10,
    timerFrame = 11,
    timeScore = 12,
    totalScore = 13
};
struct InitUIData
{
    int drawX;
    int drawY;
    int width;
    int height;
    int xNum;
    int yNum;
    std::string graphPass;
    float size;
};
struct  UIData
{
    int x;
    int y;
    int width;
    int height;
    int graphNum;
    std::vector<int> dataHandle;
    float size;
};