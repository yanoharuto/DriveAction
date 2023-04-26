#pragma once
#include <vector>
#include <string>
#include <unordered_map>
enum UIKind;
struct InitUIData;
struct UIData;
/// <summary>
/// UI��Z�߂�}�l�[�W���[
/// </summary>
class UIManager
{
public:
    /// <summary>
    /// �R���X�g���N�^
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
    //�Q�[���̖ڕW
    gamePurose = 0 ,
    //���W���̃A�C�R��
    collectIcon = 1,
    //�J�E���g�_�E��
    countDown = 2,
    //���W���̃X�R�A�\��
    collectScore = 3,
    //�_���[�W���󂯂�ƌ�������X�R�A�\��
    damageScore = 4,
    //�^�C���@��X�R�A�̕\��
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