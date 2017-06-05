#include "../include/PlayerInfo.h"

PlayerInfo::PlayerInfo(string n)
{
    name = n;
    index = 0;
    shipCount = 5;
}

PlayerInfo::~PlayerInfo()
{
    //dtor
}
