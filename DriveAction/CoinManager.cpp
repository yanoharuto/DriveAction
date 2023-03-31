#include "CoinManager.h"
#include "CourceDataLoader.h"
#include "Utility.h"
/// <summary>
/// �R�C���̐ݒu
/// </summary>
CoinManager::CoinManager()
{
    std::list<VECTOR> posList = CourceDataLoader::GetVECTORData(coinPosPass);
    coinFirstNum = posList.size();
    for (auto ite = posList.begin(); ite != posList.end(); ite++)
    {
        Coin* newCoin = new Coin((*ite));
        coinList.push_back(newCoin);
    }
}

CoinManager::~CoinManager()
{
    for (auto ite = coinList.begin(); ite != coinList.end(); ite++)
    {
        SAFE_DELETE((*ite));
    }
    coinList.clear();
}
/// <summary>
/// coinPosList�̍X�V�Ǝ��ꂽ�R�C���̍폜
/// </summary>
void CoinManager::Update()
{
    coinPosList.clear();
    auto objIte = coinList.begin();
    std::list<Coin*> brokenList;
    //�X�V����K�v�������Ȃ��������
    while (objIte != coinList.end())
    {
        //��]��������
        (*objIte)->Update();
        if (!(*objIte)->GetAliveFlag()) //�������݂��Ă��Ȃ�������X�V�I��
        {
            //�󂷂��̃��X�g�ɒǉ�
            brokenList.push_back((*objIte));
            //erase�͏������C�e���[�^�[�̎��̓z��Ԃ�
            objIte = coinList.erase(objIte);
        }
        else
        {
            //�R�C���̈ʒu���X�V
            coinPosList.push_back((*objIte)->GetPos());
            //���������ɍ���Ȃ������玟
            ++objIte;
        }
    }
    //�����Ă��������
    for (auto ite = brokenList.begin(); ite != brokenList.end(); ite++)
    {
        SAFE_DELETE(*ite);
    }
}
/// <summary>
/// �R�C���̕`��
/// </summary>
void CoinManager::Draw()
{
    for (auto ite = coinList.begin(); ite != coinList.end(); ite++)
    {
        (*ite)->Draw();
    }
}

/// <summary>
/// �R�C���̈ʒu
/// </summary>
/// <returns></returns>
std::list<VECTOR> CoinManager::GetCoinPosList()
{
    return coinPosList;
}
/// <summary>
/// �R�C���̏�������
/// </summary>
/// <returns></returns>
int CoinManager::GetCoinFirstNum()
{
    return coinFirstNum;
}
/// <summary>
/// �R�C���̌��݂̖���
/// </summary>
/// <returns></returns>
int CoinManager::GetCoinNowNum()
{
    return coinList.size();
}

