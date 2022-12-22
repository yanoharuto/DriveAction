#include "CircuitTrack.h"

CircuitTrack::CircuitTrack()
{
    modelHandele = MV1LoadModel("data/model/Circuit/RaceCircuit.mv1");
    position = VGet(0, 0, 0);
    scale = VGet(scaleValue, scaleValue, scaleValue);
    MV1SetScale(modelHandele, scale);
}

CircuitTrack::~CircuitTrack()
{
    MV1DeleteModel(modelHandele);
}

void CircuitTrack::Draw()
{
    MV1DrawModel(modelHandele);
}
