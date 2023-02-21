#include "RacerGenerater.h"
#include "Player.h"
#include "CPU.h"
#include "CourceDataLoader.h"
RacerGenerater::RacerGenerater(int racerNum)
{
    std::list<VECTOR> firstPosList = CourceDataLoader::GetCarFirstPosList();
    //�ŏ��̈�s�͌��������Ȃ̂ŏ���
    firstPosList.erase(firstPosList.begin());
    //�|�W�V�����̃C�e���[�^�[
    auto firstPosIte = firstPosList.begin();
    Racer* newRacer;
    //���[�T�[�̐�����New����
    for (int i = 0; i < racerNum + 1; i++)
    {
        firstPosIte++;
        if (i == 0)
        {
            newRacer = new Player(*firstPosIte);
        }
        else
        {
            newRacer = new CPU(*firstPosIte);
        }
        racerList.push_front(newRacer);
    }
}

std::list<Racer*> RacerGenerater::GetRacerList()
{
    return racerList;
}
