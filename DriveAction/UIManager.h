#pragma once
#include <vector>
#include "UI.h"
#include <string>
class UIManager
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <returns></returns>
    UIManager();
    ~UIManager();
    /// <summary>
    /// UI追加
    /// </summary>
    /// <param name="ui">ベクターの何番目のUIなのか返すよ</param>
    /// <returns></returns>
    int AddUI(UI* ui);
    void Update(int index,std::string updateString);
    void Update(int index,int x,int y);
    /// <summary>
    /// 描画
    /// </summary>
    void DrawUI();
    /// <summary>
    /// 追加したときの添え字のUIを消すよ
    /// </summary>
    /// <param name="uiNum"></param>
    void DeleteArgumentUI(int uiNum);
    /// <summary>
    /// ベクターに追加したUI全消し
    /// </summary>
    void DeleteAllUI();
    /// <summary>
    /// 描画をいったん止める用
    /// </summary>
    /// <param name="uiNum"></param>
    /// <param name="boolValue"></param>
    void StopArgumentDrawUI(int uiNum, bool boolValue);
private:
    std::vector<UI*> uiVec;
};
