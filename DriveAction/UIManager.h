#pragma once
#include <vector>
#include "UI.h"
#include <string>
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
    /// <summary>
    /// UI�ǉ�
    /// </summary>
    /// <param name="ui">�x�N�^�[�̉��Ԗڂ�UI�Ȃ̂��Ԃ���</param>
    /// <returns></returns>
    int AddUI(UI* ui);
    void Update(int index,std::string updateString);

    void Update(int index,int x,int y);
    /// <summary>
    /// �`��
    /// </summary>
    void DrawUI();
    /// <summary>
    /// �ǉ������Ƃ��̓Y������UI��������
    /// </summary>
    /// <param name="uiNum"></param>
    void DeleteArgumentUI(int uiNum);
    /// <summary>
    /// �x�N�^�[�ɒǉ�����UI�S����
    /// </summary>
    void DeleteAllUI();
 private:
    std::vector<UI*> uiVec;
};
