#pragma once
#include <list>
#include "DxLib.h"
struct CircuitData
{
    //Ô‚ªŸ‚És‚­‚×‚«s‚«æ‚ª‘‚¢‚Ä‚ ‚é
    std::list<VECTOR> positionVec;
    //‹t‘–‚µ‚ÄƒS[ƒ‹‚µ‚È‚¢‚æ‚¤‚É•ûŒü‚àæ‚¹‚é
    std::list<VECTOR> directionVec;
};