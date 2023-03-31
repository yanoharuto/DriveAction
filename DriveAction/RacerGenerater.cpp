#include "RacerGenerater.h"
#include "CPU.h"
#include "CourceDataLoader.h"

RacerGenerater::RacerGenerater()
{
}
void RacerGenerater::CreateRacers(int racerNum, std::list<Racer*>* racerList, Player** player, PlayerInformationCenter* infoCenter)
{
    std::list<VECTOR> firstPosList = CourceDataLoader::GetVECTORData(firstPosPass);
    //�|�W�V�����̃C�e���[�^�[
    auto firstPosIte = firstPosList.begin();
    
    //���[�T�[�̐�����New����
    Racer* newRacer;
    for (int i = 0; i < racerNum + 1; i++)
    {
        if (i == 0)
        {
            (*player) = new Player(*firstPosIte);
            newRacer =(*player);
            infoCenter->AddPlayer((*player));
        }
        else
        {
            newRacer = new CPU(*firstPosIte);
        }
        (*racerList).push_front(newRacer);
        firstPosIte++;
    }

}